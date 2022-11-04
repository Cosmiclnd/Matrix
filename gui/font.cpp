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

#include "font.hpp"
#include "../functions.hpp"

#include <SDL2/SDL_image.h>

SDL_Surface *g_sgaLetters, *g_asciiLetters;
Sga g_sga;
Ascii g_ascii;

void Sga::blit(SDL_Surface *surface, SDL_Rect *rect)
{
	char c;
	int index = 0;
	for (int i = 0; i < string.length(); i++) {
		if (c == '$') {
			if (string[i] == '$') {
				c = '$';
			}
			else if ('0' <= string[i] && string[i] <= '9') {
				c = '-' + string[i] - '0';
			}
			else if ('a' <= string[i] && string[i] <= 'j') {
				c = '7' + string[i] - 'a';
			}
			if ('-' <= c && c <= '@') {
				index++;
				blitChar(surface, c, rect->x + index * style.size, rect->y, style);
				continue;
			}
		}
		else {
			c = string[i];
			if (c == '$') continue;
		}
		index++;
		if (('a' <= c && c <= 'z') ||
			('A' <= c && c <= 'Z')) {
			blitChar(surface, c, rect->x + index * style.size, rect->y, style);
		}
		else {
			g_ascii.blitChar(
				surface, c, rect->x + index * style.size, rect->y, style);
		}
	}
}

void Sga::blitChar(
	SDL_Surface *surface, char c, int x, int y, FontStyle style_)
{
	int ln = c / 16, col = c % 16;
	SDL_Rect rect1 = { col << 3, ln << 3, 8, 8 };
	SDL_Rect rect2 = { x, y, style_.size, style_.size };
	SDL_BlitScaled(g_sgaLetters, &rect1, surface, &rect2);
}

void Ascii::blit(SDL_Surface *surface, SDL_Rect *rect)
{
	char c;
	int index = 0;
	for (int i = 0; i < string.length(); i++) {
		if (c == '$') {
			if (string[i] == '$') {
				c = '$';
			}
			else {
				if ('0' <= string[i] && string[i] <= '9') {
					c = '-' + string[i] - '0';
				}
				else if ('a' <= string[i] && string[i] <= 'j') {
					c = '7' + string[i] - 'a';
				}
				else if ('A' <= string[i] && string[i] <= 'Z') {
					c = string[i];
				}
				index++;
				g_sga.blitChar(
					surface, c, rect->x + index * style.size, rect->y, style);
				continue;
			}
		}
		else {
			c = string[i];
			if (c == '$') continue;
		}
		index++;
		blitChar(surface, c, rect->x + index * style.size, rect->y, style);
	}
}

void Ascii::blitChar(
	SDL_Surface *surface, char c, int x, int y, FontStyle style_)
{
	int ln = c / 16, col = c % 16;
	SDL_Rect rect1 = { col << 3, ln << 3, 8, 8 };
	SDL_Rect rect2 = { x, y, style_.size, style_.size };
	SDL_BlitScaled(g_asciiLetters, &rect1, surface, &rect2);
}

void initFont()
{
	g_sgaLetters = tryLoadImage("assets/matrix/textures/font/sga.png");
	if (!g_sgaLetters) {
		g_logger->crash(
			"Resource pack is damaged, failed to load SGA Letters");
	}
	g_asciiLetters = tryLoadImage("assets/matrix/textures/font/ascii.png");
	if (!g_asciiLetters) {
		g_logger->crash(
			"Resource pack is damaged, failed to load ASCII Letters");
	}
}
