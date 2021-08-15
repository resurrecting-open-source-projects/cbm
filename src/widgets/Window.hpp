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

#ifndef CBM_WIDGETS_WINDOW_HPP
#define CBM_WIDGETS_WINDOW_HPP

#include "Screen.hpp"
#include <string>

class Window {
public:
    Window(Screen& screen);
    virtual ~Window();

    void setPosition(unsigned x, unsigned y);
    void setSize(unsigned width, unsigned height);
    unsigned getWidth() const;
    unsigned getHeight() const;

protected:
    virtual void update() const;

    void clear() const;

    void setStyle(int style) const;
    void setBackground(int background) const;
    void putHLine(int x, int y, int ch, unsigned num) const;
    void putString(int x, int y, const std::string& text) const;

private:
    Window(const Window&);
    void operator=(const Window&);

    Screen& screen_;
    void* win_;

    friend class Screen;
};

#endif
