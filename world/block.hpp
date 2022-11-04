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

#ifndef __WORLD_BLOCK_HPP
#define __WORLD_BLOCK_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include <exception>

#include "../settings.hpp"
#include "../registry.hpp"

class AmbigousBlockError : std::exception {
	const char *what() const noexcept
	{ return "block registry is ambigious"; };
};

class BadBlockType : std::exception {
	const char *what() const noexcept
	{ return "bad block type"; };
};

class Block {
	double hardness;
	SDL_Surface *surface;
	bool mask[Settings::BLOCK_LENGTH_PIXEL][Settings::BLOCK_LENGTH_PIXEL];

public:
	Block();
	virtual SDL_Surface *getSurface();
	virtual void setSurface(SDL_Surface *surface_);
	virtual bool collide(int i, int j) { return mask[i][j]; }
};

class BlockRegistry {
	Block *blocks[Settings::MAX_BLOCKS];
	std::unordered_map<std::string, int> map;
	int present;

public:
	BlockRegistry();
	int registered(ResourceLocation name, Block *block);
	Block *getRegistered(int id);
	Block *getRegistered(std::string name);
	void loadDebugTexture(ResourceLocation name, Block *block);
};

namespace Blocks {
	extern int STONE;
	extern int DIRT;
	extern int GRASS_BLOCK;
};

void initBlock();

extern BlockRegistry blockRegistry;

#endif
