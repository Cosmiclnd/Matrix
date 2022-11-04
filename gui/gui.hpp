#ifndef __GUI_GUI_HPP
#define __GUI_GUI_HPP

#include "screen.hpp"

class GuiLayer {
	Screen *screen;

public:
	GuiLayer(Screen *s);
	~GuiLayer();
	void update(bool show);
};

#endif
