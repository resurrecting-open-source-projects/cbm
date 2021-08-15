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

#include "Screen.hpp"
#include "Window.hpp"
#include <curses.h>

Screen::Screen() {
    initscr();
    win_ = stdscr;
}

Screen::~Screen() {
    endwin();
}

void Screen::update() {
    // First, touch self to force updates of the children
    touchwin((WINDOW*) win_);

    // Update the children
    for (Children::const_iterator child = children_.begin();
            child != children_.end(); ++child)
        (*child)->update();

    // Flush the changes
    doupdate();
}

void Screen::addChild(Window* window) {
    children_.insert(window);
}

void Screen::removeChild(Window* window) {
    children_.erase(window);
}

unsigned Screen::getWidth() const {
    int y, x;
    getmaxyx((WINDOW*) win_, y, x);
    return x;
}

unsigned Screen::getHeight() const {
    int y, x;
    getmaxyx((WINDOW*) win_, y, x);
    return y;
}
