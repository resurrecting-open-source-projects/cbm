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
