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

#include "cursor.hpp"
#include "texture.hpp"

static SDL_Cursor *now;

SDL_Cursor *getCursor()
{
	return now;
}

void setCursor(SDL_Cursor *cursor)
{
	if (cursor == now) return;
	now = cursor;
	if (!cursor) {
		SDL_ShowCursor(SDL_DISABLE);
		return;
	}
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetCursor(cursor);
}

namespace Cursors {
	SDL_Cursor *NONE;
	SDL_Cursor *DEFAULT;
	SDL_Cursor *PICKAXE;
	SDL_Cursor *SWORD;
	SDL_Cursor *SELECTED;
}

void initCursor()
{
	Cursors::NONE = 0;
	Cursors::DEFAULT = SDL_GetDefaultCursor();
	Cursors::PICKAXE = SDL_CreateColorCursor(
		textureRegistry.getRegistered("matrix:pickaxe"), 7, 7);
	Cursors::SWORD = SDL_CreateColorCursor(
		textureRegistry.getRegistered("matrix:sword"), 7, 7);
	Cursors::SELECTED = SDL_CreateColorCursor(
		textureRegistry.getRegistered("matrix:selected"), 7, 7);
	setCursor(Cursors::DEFAULT);
}
