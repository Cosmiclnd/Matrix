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

#ifndef __GUI_CURSOR_HPP
#define __GUI_CURSOR_HPP

#include <SDL2/SDL.h>

namespace Cursors {
	extern SDL_Cursor *NONE;
	extern SDL_Cursor *DEFAULT;
	extern SDL_Cursor *PICKAXE;
	extern SDL_Cursor *SWORD;
	extern SDL_Cursor *SELECTED;
}

SDL_Cursor *getCursor();
void setCursor(SDL_Cursor *cursor);

void initCursor();

#endif
