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
