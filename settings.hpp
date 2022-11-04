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

#ifndef __MATRIX_SETTINGS_HPP
#define __MATRIX_SETTINGS_HPP

#include <chrono>

namespace Settings {
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 500;
	const int BLOCK_LENGTH_PIXEL = 24;
	const int CHUNK_LENGTH_PIXEL = BLOCK_LENGTH_PIXEL << 4;
	const int CHUNKS_SHOWW = (WINDOW_WIDTH + 2 * CHUNK_LENGTH_PIXEL - 1) /
		CHUNK_LENGTH_PIXEL;
	const int CHUNKS_SHOWH = (WINDOW_HEIGHT + 2 * CHUNK_LENGTH_PIXEL - 1) /
		CHUNK_LENGTH_PIXEL;

	const int MAX_BLOCKS = 512;
	const int MAX_SCREENS = 256;
	const int MAX_HOOKS = 256;

	const int TPS = 20;
	const std::chrono::nanoseconds UPDATE_TICK_NANO =
		std::chrono::nanoseconds(1000000000 / TPS);

	extern int FPS;
};

#endif
