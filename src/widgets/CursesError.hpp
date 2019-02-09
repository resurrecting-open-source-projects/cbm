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

#ifndef CBM_WIDGETS_CURSESERROR_HPP
#define CBM_WIDGETS_CURSESERROR_HPP

#include <stdexcept>
#include <string>

class CursesError : public std::runtime_error {
    public:
	CursesError(const std::string& description) : std::runtime_error(description) {}
};

#endif
