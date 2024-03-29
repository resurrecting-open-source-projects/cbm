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

#ifndef CBM_WIDGETS_SCREEN_HPP
#define CBM_WIDGETS_SCREEN_HPP

#include <set>

class Window;

class Screen {
public:
    Screen();
    ~Screen();

    unsigned getWidth() const;
    unsigned getHeight() const;

    void update();

private:
    Screen(const Screen&);
    void operator=(const Screen&);

    void addChild(Window* window);
    void removeChild(Window* window);

    void* win_;
    friend class Window;
    typedef std::set<Window*> Children;
    Children children_;
};

#endif
