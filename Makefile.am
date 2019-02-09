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

SUBDIRS=doc src
EXTRA_DIST=COPYING debian/*

ACLOCAL_AMFLAGS = -I m4

distclean-local:
	-rm -rf autom4te.cache/ \
	m4/*

	-rm -f *~ \
	aclocal.m4 \
	compile \
	config.* \
	configure \
	depcomp \
	install-sh \
	ltmain.sh \
	Makefile.in \
	missing \
	doc/Makefile.in
