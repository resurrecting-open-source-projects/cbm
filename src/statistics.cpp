/*
  Color Bandwidth Meter (CBM) - display in real time the network traffic speed

  Copyright 2005-2006 Aaron Isotton <aaron@isotton.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; version 2
  of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "config.h"
#include "statistics.hpp"
#include "ErrnoError.hpp"
#include <algorithm>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define PROC_NET_DEV "/proc/net/dev"

namespace statistics {

Interface::Interface(const std::string& name) : name_(name), updated_(false) {}

class InterfaceNameMatchesPredicate {
    public:
	InterfaceNameMatchesPredicate(const std::string& name) : name_(name) {}

	bool operator() (const Interface& interface) const { 
	    return name_ == interface.getName(); 
	}
    private:
	std::string name_;
};

class InterfaceNotUpdatedPredicate {
    public:
	bool operator() (const Interface& interface) const { 
	    return !interface.getUpdated(); 
	}
};

void Interface::update(const Statistics& statistics) {
    memcpy(statistics_ + 1, statistics_ + 0, sizeof(Statistics));
    memcpy(statistics_, &statistics, sizeof(Statistics));
   
    const Statistics& x0 = statistics_[1];
    const Statistics& x1 = statistics_[0];
    
    double timeDelta = 
	(x1.timestamp.tv_sec - x0.timestamp.tv_sec) * 1.
      + (x1.timestamp.tv_usec - x0.timestamp.tv_usec) * .000001;

    receiveSpeed_ = (x1.rx_bytes - x0.rx_bytes) / timeDelta;
    transmitSpeed_ = (x1.tx_bytes - x0.tx_bytes) / timeDelta;

    updated_ = true;
}

void Reader::update() {
    // Open /proc/net/dev
    FILE *dev = fopen(PROC_NET_DEV, "r");
    if (!dev) 
	throw ErrnoError("cannot open " PROC_NET_DEV);

    try {
	// Clear the 'updated' flag for all interfaces
	for (Interfaces::iterator interface = interfaces_.begin();
		interface != interfaces_.end(); ++interface)
	    interface->setUpdated(false);

	// Read /proc/dev/net
	while (!feof(dev)) {
	    char buf[500];
	    char *name, *statistics_string;
	    Statistics stats;
	    struct timezone unused_timezone;

	    // Read a line
	    fgets(buf, sizeof(buf), dev);
	    gettimeofday(&stats.timestamp, &unused_timezone);

	    // Find the colon separating the name from the statistics
	    statistics_string = strchr(buf, ':');
	    if (!statistics_string) continue;

	    // Get a pointer to the statistics
	    *statistics_string = 0;
	    ++statistics_string;

	    // Remove leading whitespace from the name
	    name = buf;
	    while (*name == ' ' || *name == '\t') ++name;
	    
	    // Parse the statistics
	    if (sscanf(statistics_string, "%Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu "
					  "%Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu",
			    &stats.rx_bytes, &stats.rx_packets, 
			    &stats.rx_errs, &stats.rx_drop, 
			    &stats.rx_fifo, &stats.rx_frame, 
			    &stats.rx_compressed, &stats.rx_multicast,
			    &stats.tx_bytes, &stats.tx_packets, 
			    &stats.tx_errs, &stats.tx_drop, 
			    &stats.tx_fifo, &stats.tx_frame, 
			    &stats.tx_compressed, &stats.tx_multicast) 
		    == 16) {
		
		// Find the interface with the same name
		Interfaces::iterator interface 
		    = std::find_if(interfaces_.begin(), interfaces_.end(), 
			InterfaceNameMatchesPredicate(name));
		
		if (interface == interfaces_.end()) {
		    // This is a new interface; add it to the list
		    interfaces_.push_back(Interface(name));
		    interface = interfaces_.end();
		    --interface;
		}
		
		// Update the interface
		interface->update(stats);
	    }
	}

	// Remove all interfaces for which the updated flag was not set
	interfaces_.remove_if(InterfaceNotUpdatedPredicate());
	
	// Close the file
	fclose(dev);
    }
    catch (...) {
	fclose(dev);
	throw;
    }
}

void Interface::setUpdated(bool updated) {
    updated_ = updated;
}

bool Interface::getUpdated() const {
    return updated_;
}

const std::string& Interface::getName() const {
    return name_;
}

double Interface::getReceiveSpeed() const {
    return receiveSpeed_;
}

double Interface::getTransmitSpeed() const {
    return transmitSpeed_;
}

const Reader::Interfaces& Reader::getInterfaces() const {
    return interfaces_;
}

} // namespace statistics
