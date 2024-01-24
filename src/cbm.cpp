/*
  Color Bandwidth Meter (CBM) - display in real time the network traffic speed

  Copyright 2005-2006 Aaron Isotton <aaron@isotton.com>
  Copyright 2006      Paul Martin <pm@debian.org>
  Copyright 2012      Cyril Brulebois <kibi@debian.org>
  Copyright 2020      daltomi <daltomi@disroot.org>

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
#include "ErrnoError.hpp"
#include "statistics.hpp"
#include "widgets/Bar.hpp"
#include "widgets/VerticalTable.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <curses.h>
#include <getopt.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>

// Externs
extern int optind, opterr, optopt;

namespace {

// Globals
static const char* optstring = "hV";

struct option longopts[] =
{
    { "help",       no_argument,    NULL, 'h' },
    { "version",    no_argument,    NULL, 'V' },
    {  NULL,        0,              NULL,  0  }
};

volatile bool quit = false;

void endHandler(int signum) {
    quit = true;
}

std::string formatBandwidth(double bytesPerSecond, bool showBits) {
    const char* prefixes[] = { "", "k", "M", "G", "T", "P", "E", "Z", "Y" };

    // Calculate the value
    double value;
    const char* unit;
    if (showBits) {
        value = bytesPerSecond * 8;
        unit = "b/s";
    }
    else {
        value = bytesPerSecond;
        unit = "B/s";
    }

    // Choose the prefix
    unsigned prefix = 0;
    while (prefix < (sizeof(prefixes) / sizeof(const char*))
            && value > 1000.) {
        value /= 1000.;
        ++prefix;
    }

    // Format the string
    std::ostringstream s;
    s << std::setw(8) << std::fixed << std::setprecision(2)
      << value << " " << prefixes[prefix] << unit;

    return s.str();
}

void usage(std::ostream& out) {
    out <<
        "Usage: " PACKAGE " [OPTIONS]\n"
        "Display the current traffic on all network devices\n"
        "\n"
        "Options:\n"
        "  --help     Display this help and exit\n"
        "  --version  Display version information and exit\n";
}

} // anonymous namespace

enum {
    COLOR_TITLE = 1,
    COLOR_HEADING,
    COLOR_STATUSBAR
};

int main(int argc, char **argv) {
    int retval = EXIT_SUCCESS;

    try {
        // parse the command line
        opterr = 0;
        bool getopt_done = false;
        while (!getopt_done) {
            int ch = getopt_long(argc, argv, optstring, longopts, NULL);
            switch (ch) {
            case 'h':
                usage(std::cout);
                return EXIT_SUCCESS;

            case 'V':
                puts(PACKAGE_STRING);
                return EXIT_SUCCESS;

            case '?':
                std::cerr << PACKAGE ": invalid option: -"
                          << static_cast<char>(optopt)
                          << "; try --help for usage information\n";
                return EXIT_FAILURE;

            case -1:
                getopt_done = true;
                break;
            }
        }

        // Catch SIGINT
        signal(SIGINT, endHandler);

        int interval = 1000;

        // Create a socket (for ioctls)
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (!sock) throw ErrnoError("cannot open socket");

        try {
            // Initialize curses
            Screen screen;
            nonl();
            cbreak();
            noecho();
            timeout(interval);
            curs_set(0);
            keypad(stdscr, TRUE);

            if (has_colors()) {
                start_color();
                init_pair(COLOR_TITLE,	COLOR_WHITE, 	COLOR_BLUE);
                init_pair(COLOR_HEADING, 	COLOR_RED, 	COLOR_BLACK);
                init_pair(COLOR_STATUSBAR, 	COLOR_WHITE, 	COLOR_BLUE);
            }

            // Create the title and status bars
            Bar titleBar(screen);
            titleBar.setStyle(COLOR_PAIR(COLOR_TITLE) | A_BOLD);
            titleBar.setBackground(' ' | COLOR_PAIR(COLOR_TITLE));

            Bar statusBar(screen);
            statusBar.setStyle(COLOR_PAIR(COLOR_STATUSBAR) | A_BOLD);
            statusBar.setBackground(' ' | COLOR_PAIR(COLOR_STATUSBAR));

            // Create the interface table
            VerticalTable interfaceTable(screen);
            interfaceTable.setColumns(6);
            interfaceTable.setActiveStyle(A_BOLD);
            interfaceTable.setActiveRow(1);
            // Position the interface table
            interfaceTable.setPosition(2, 2);
            interfaceTable.setSize(screen.getWidth() - 4,
                                   8); // TODO

            // Create the detail table
            VerticalTable detailTable(screen);
            detailTable.setColumns(2);
            detailTable.setRows(2);
            detailTable.setActiveRow(-1);
            // Position the detail table
            detailTable.setPosition(2, 12); // TODO
            detailTable.setSize(screen.getWidth() - 4, 10); // TODO

            // Populate the detail table
            detailTable.setText (0, 0, "Interface");
            detailTable.setStyle(0, 0, COLOR_PAIR(COLOR_HEADING) | A_BOLD);
            detailTable.setStyle(1, 1, A_NORMAL);

            detailTable.setText (0, 1, "Address");
            detailTable.setStyle(0, 1, COLOR_PAIR(COLOR_HEADING) | A_BOLD);
            detailTable.setStyle(1, 1, A_NORMAL);

            bool bit_mode = false;

            statistics::Reader statisticsReader;

            while (!quit) {
                // Read the keyboard input
                int ch = getch();
                switch (ch) {
                case 'b':
                    bit_mode = !bit_mode;
                    break;

                case 'q':
                    quit = true;
                    break;

                case '+':
                    interval += 100;
                    timeout(interval);
                    break;

                case '-':
                    if (interval > 100) interval -= 100;
                    timeout(interval);
                    break;

                case 'p':
                case KEY_UP:
                    interfaceTable.setActiveRow(
                        std::max(static_cast<int>(
                                     interfaceTable.getActiveRow() - 1), 1));
                    break;

                case 'n':
                case KEY_DOWN:
                    interfaceTable.setActiveRow(
                        std::min(static_cast<int>(
                                     interfaceTable.getActiveRow() + 1),
                                 static_cast<int>(
                                     interfaceTable.getRows()) - 1));
                    break;
                }

                // Update the statistics
                statisticsReader.update();

                // Populate the interface table
                interfaceTable.setRows(
                    statisticsReader.getInterfaces().size() + 1);

                interfaceTable.setText (0, 0, "Interface");
                interfaceTable.setStyle(0, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                interfaceTable.setText (1, 0, " Receive");
                interfaceTable.setStyle(1, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                interfaceTable.setText (2, 0, "Transmit");
                interfaceTable.setStyle(2, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                interfaceTable.setText (3, 0, "   Total");
                interfaceTable.setStyle(3, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                interfaceTable.setText (4, 0, "Receive Max");
                interfaceTable.setStyle(4, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                interfaceTable.setText (5, 0, "Transmit Max");
                interfaceTable.setStyle(5, 0,
                                        COLOR_PAIR(COLOR_HEADING) | A_BOLD);

                unsigned index = 1;
                for (statistics::Reader::Interfaces::const_iterator
                        interface = statisticsReader.getInterfaces().begin();
                        interface != statisticsReader.getInterfaces().end();
                        ++interface) {

                    interfaceTable.setText (0, index, interface->getName());
                    interfaceTable.setStyle(0, index, A_NORMAL);

                    interfaceTable.setText (1, index,
                                            formatBandwidth(interface->getReceiveSpeed(),
                                                            bit_mode));
                    interfaceTable.setStyle(1, index, A_NORMAL);

                    interfaceTable.setText (2, index,
                                            formatBandwidth(interface->getTransmitSpeed(),
                                                            bit_mode));
                    interfaceTable.setStyle(2, index, A_NORMAL);

                    interfaceTable.setText (3, index,
                                            formatBandwidth(interface->getReceiveSpeed()
                                                            + interface->getTransmitSpeed(), bit_mode));
                    interfaceTable.setStyle(3, index, A_NORMAL);

                    interfaceTable.setText(4, index,
                                            formatBandwidth(interface->getReceiveMax(), bit_mode));
                    interfaceTable.setStyle(4, index, A_NORMAL);

                    interfaceTable.setText(5, index,
                                            formatBandwidth(interface->getTransmitMax(), bit_mode));
                    interfaceTable.setStyle(5, index, A_NORMAL);

                    if (index == interfaceTable.getActiveRow()) {
                        // Get the details for the active interface
                        struct ifreq req;
                        strcpy(req.ifr_name, interface->getName().c_str());
                        if (ioctl(sock, SIOCGIFADDR, &req)) {
                            detailTable.setText(1, 1, "N/A");
                        }
                        else {
                            char addrString[100];
                            struct sockaddr_in *addr
                                    = reinterpret_cast<struct sockaddr_in*>(
                                          &req.ifr_addr);
                            inet_ntop(addr->sin_family,
                                      &addr->sin_addr,
                                      addrString, 100);

                            detailTable.setText(1, 1, addrString);
                        }

                        detailTable.setText(1, 0, interface->getName());
                    }

                    ++index;
                }

                // Position the title
                titleBar.setPosition(0, 0);
                titleBar.setSize(screen.getWidth(), 1);
                titleBar.setText("Color Bandwidth Meter");

                // Position the status bar
                statusBar.setPosition(0, screen.getHeight() - 1);
                statusBar.setSize(screen.getWidth(), 1);
                std::ostringstream s;
                s << "Up/down | q Quit | b Bits/Bytes | "
                  "+- Update interval (" << interval << "ms)";
                statusBar.setText(s.str());

                // Position the interface table
                interfaceTable.setPosition(2, 2);
                interfaceTable.setSize(screen.getWidth() - 4,
                                       8); // TODO

                // Position the detail table
                detailTable.setPosition(2, 12); // TODO
                detailTable.setSize(screen.getWidth() - 4, 10); // TODO

                // Update everything
                screen.update();
            }
        }
        catch (...) {
            close(sock);
            throw;
        }
        close(sock);
    } catch (const std::exception& e) {
        std::cerr << PACKAGE << ": " << e.what() << '\n';
        retval = EXIT_FAILURE;
    }
    return retval;
}
