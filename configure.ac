#
#  Color Bandwidth Meter (CBM) - display in real time the network traffic speed
#
#  Copyright 2005-2006 Aaron Isotton <aaron@isotton.com>
#  Copyright 2019      Joao Eriberto Mota Filho <eriberto@debian.org>
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; version 2
#  of the License.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

AC_PREREQ(2.59)
AC_INIT([cbm],[0.2],[https://github.com/resurrecting-open-source-projects/cbm/issues])
AM_INIT_AUTOMAKE(foreign)
AC_CONFIG_SRCDIR(src/cbm.cpp)
AC_CONFIG_HEADER(src/config.h)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
if test "${GXX}" = ""; then
    AC_MSG_ERROR([ERROR: we need a C++ compiler, like g++ or other])
fi
AC_PROG_LIBTOOL

# Check for host platform
AC_CANONICAL_HOST

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER(curses.h,[],[ AC_MSG_ERROR(curses.h not found or too old.) ], [])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
#
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_FILES([Makefile doc/Makefile src/Makefile src/widgets/Makefile])
AC_OUTPUT
