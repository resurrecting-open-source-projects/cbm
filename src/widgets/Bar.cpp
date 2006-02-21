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

