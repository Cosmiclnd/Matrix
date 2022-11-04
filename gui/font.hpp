#ifndef __GUI_FONT_HPP
#define __GUI_FONT_HPP

#include <SDL2/SDL.h>
#include <string>

struct FontStyle {
	unsigned int fg, bg;
	int size;
};

class Sga {
	std::string string;
	FontStyle style;

public:
	Sga *setString(std::string new_) { string = new_; return this; }
	Sga *setStyle(FontStyle style_) { style = style_; return this; }
	void blit(SDL_Surface *surface, SDL_Rect *rect);
	void blitChar(SDL_Surface *surface, char c, int x, int y, FontStyle style_);
};

class Ascii {
	std::string string;
	FontStyle style;

public:
	Ascii *setString(std::string new_) { string = new_; return this; }
	Ascii *setStyle(FontStyle style_) { style = style_; return this; }
	void blit(SDL_Surface *surface, SDL_Rect *rect);
	void blitChar(SDL_Surface *surface, char c, int x, int y, FontStyle style_);
};

void initFont();

extern SDL_Surface *g_sgaLetters, *g_asciiLetters;
extern Sga g_sga;
extern Ascii g_ascii;

#endif
