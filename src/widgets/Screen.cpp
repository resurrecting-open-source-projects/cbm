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
