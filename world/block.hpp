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
