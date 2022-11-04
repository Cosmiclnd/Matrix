/*

Copyright (C) 2022 Cosmicland

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

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
