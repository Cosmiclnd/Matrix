#include "gui.hpp"

GuiLayer::GuiLayer(Screen *s)
	: screen(s)
{
}

GuiLayer::~GuiLayer()
{
	delete screen;
}

void GuiLayer::update(bool show)
{
	screen->update(show);
}
