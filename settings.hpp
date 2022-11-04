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
