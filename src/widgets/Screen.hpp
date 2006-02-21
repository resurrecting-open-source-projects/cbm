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
