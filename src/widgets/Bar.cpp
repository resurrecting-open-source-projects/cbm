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

#include "Bar.hpp"

Bar::Bar(Screen& screen) : Window(screen), style_(0), background_(' ') {}

void Bar::setText(const std::string& text) {
    text_ = text;
}

void Bar::setStyle(int style) {
    style_ = style;
}

void Bar::setBackground(int background) {
    background_ = background;
}

void Bar::update() const {
    Window::setStyle(style_);
    Window::setBackground(background_);
    Window::clear();
    Window::putString(1, 0, text_);
    Window::update();
}

