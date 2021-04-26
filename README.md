# CBM (Color Bandwidth Meter)

#### cbm - display in real time the network traffic speed

## Help this project ##

CBM needs your help. **If you are a programmer** and if you wants to help a
nice project, this is your opportunity.

CBM was imported from some tarballs from Debian Project[1].
After this, all patches found in Debian project and other places for this program
were applied. All initial work was registered in ChangeLog file (version 0.2 and
later releases). CBM is packaged in Debian[2] Project.

If you are interested to help CBM, read the [CONTRIBUTING.md](CONTRIBUTING.md) file.

[1] http://snapshot.debian.org/package/cbm/
[2] https://tracker.debian.org/pkg/cbm

## What is CBM? ##

The Color Bandwidth Meter (CBM) is a small program to display the traffic
currently flowing through the network devices in a simple curses-based GUI.
The traffic for all interfaces include values as receive, transfer and total
Bytes/s or bits/s (or its multiples as KB/s and Kb/s).

It is useful for Internet or LAN speed tests, measuring the velocity of a
link, to establish a benchmark or to monitor your connections. CBM can be
used with virtual, wired or wireless networks.

Nowadays, CBM is maintained by volunteers.

## Build and Install ##

CBM depends of libncurses to build.

To build and install, run the following commands:

    $ ./autogen.sh
    $ ./configure
    $ make
    # make install

To return to original source code, you can use '$ make distclean' command.

On Debian systems you can use '# apt install cbm'.

## AUTHOR ##

CBM was originally developed by Aaron Isotton <aaron@isotton.com> under GPL-2.

Currently, source code and newer versions are available at
https://github.com/resurrecting-open-source-projects/cbm
