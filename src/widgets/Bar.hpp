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

#ifndef CBM_WIDGETS_BAR_HPP
#define CBM_WIDGETS_BAR_HPP

#include "Window.hpp"
#include <string>

class Bar : public Window {
    public:
	Bar(Screen& screen);

	void setText(const std::string& text);
	void setStyle(int style);
	void setBackground(int background);

    protected:
	virtual void update() const;

    private:
	int style_, background_;
	std::string text_;
};

#endif
