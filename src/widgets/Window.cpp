/*
  Color Bandwidth Meter (CBM) - display in real time the network traffic speed

  Copyright 2005-2006 Aaron Isotton <aaron@isotton.com>
  Copyright 2006      Paul Martin <pm@debian.org>

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

#include "Window.hpp"
#include "CursesError.hpp"
#include <curses.h>

Window::Window(Screen& screen) : screen_(screen) {
    win_ = derwin((WINDOW*) screen.win_, 0, 0, 0, 0);
    if (!win_) throw CursesError("cannot create new window");
    screen_.addChild(this);
}

Window::~Window() {
    screen_.removeChild(this);
    delwin((WINDOW*) win_);
}
	
void Window::setPosition(unsigned x, unsigned y) {
    mvderwin((WINDOW*) win_, y, x);
}

void Window::setSize(unsigned width, unsigned height) {
    wresize((WINDOW*) win_, height, width);
}
	
void Window::update() const {
    wnoutrefresh((WINDOW*) win_);
}

void Window::clear() const {
    werase((WINDOW*) win_);
}

void Window::putString(int x, int y, const std::string& text) const {
    mvwaddstr((WINDOW*) win_, y, x, text.c_str());
}

void Window::setStyle(int style) const {
    wattrset((WINDOW*) win_, style);
}

void Window::setBackground(int background) const {
    wbkgdset((WINDOW*) win_, background);
}

unsigned Window::getWidth() const {
    int y, x;
    getmaxyx((WINDOW*) win_, y, x);
    return x;
}

unsigned Window::getHeight() const {
    int y, x;
    getmaxyx((WINDOW*) win_, y, x);
    return y;
}

void Window::putHLine(int x, int y, int ch, unsigned num) const {
    mvwhline((WINDOW*) win_, y, x, ch, num);
}
