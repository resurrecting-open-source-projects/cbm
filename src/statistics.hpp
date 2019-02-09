/*
  Color Bandwidth Meter (CBM) - display in real time the network traffic speed

  Copyright 2005-2006 Aaron Isotton <aaron@isotton.com>
  Copyright 2007      brian m. carlson <sandals@crustytoothpaste.ath.cx>

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

#ifndef CBM_STATISTICS_H
#define CBM_STATISTICS_H

#include <list>
#include <string>
#include <sys/time.h>

namespace statistics {

struct Statistics {
    struct timeval timestamp;
    unsigned long long rx_bytes, rx_packets, rx_errs, rx_drop, rx_fifo,
		       rx_frame, rx_compressed, rx_multicast,
		       tx_bytes, tx_packets, tx_errs, tx_drop, tx_fifo,
		       tx_frame, tx_compressed, tx_multicast;
};

class Interface {
    public:
	Interface(const std::string& name);

	const std::string& getName() const;

	void setUpdated(bool updated);
	bool getUpdated() const;

	void update(const Statistics& statistics);
	
	double getReceiveSpeed() const;
	double getTransmitSpeed() const;

    private:
	std::string name_;
	bool updated_;
	Statistics statistics_[2];
	double receiveSpeed_, transmitSpeed_;
};

class Reader {
    public:
	void update();
	
	typedef std::list<Interface> Interfaces;
	const Interfaces& getInterfaces() const;
	
    private:
	Interfaces interfaces_;
};

} // namespace statistics

#endif
