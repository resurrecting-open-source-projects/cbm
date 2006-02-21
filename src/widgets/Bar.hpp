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
