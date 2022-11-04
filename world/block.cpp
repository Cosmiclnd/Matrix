#include "block.hpp"

#include <filesystem>
#include <SDL2/SDL2_rotozoom.h>

#include "../functions.hpp"

BlockRegistry blockRegistry;

Block::Block()
{
	for (int i = 0; i < Settings::BLOCK_LENGTH_PIXEL; i++) {
		for (int j = 0; j < Settings::BLOCK_LENGTH_PIXEL; j++) {
			mask[i][j] = true;
		}
	}
}

SDL_Surface *Block::getSurface()
{
	return surface;
}

void Block::setSurface(SDL_Surface *surface_)
{
	surface = surface_;
}

BlockRegistry::BlockRegistry()
	: present(0)
{
	for (int i = 0; i < Settings::MAX_BLOCKS; i++) {
		blocks[i] = 0;
	}
}

int BlockRegistry::registered(ResourceLocation name_, Block *block)
{
	std::string name = name_;
	if (map.find(name) != map.end()) throw AmbigousBlockError();
	map[name] = present;
	blocks[present++] = block;
	g_logger->info("Block %s registered, id %d", name.c_str(), present - 1);
	std::string filename = "assets/matrix/textures/block/" +
		name_.getName() + ".png";
	SDL_Surface *surface = tryLoadImage(filename);
	if (!surface) {
		g_logger->warn("Loading %s instead", filename.c_str());
		loadDebugTexture(name_, block);
		return present - 1;
	}
	block->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::BLOCK_LENGTH_PIXEL / double(surface->w),
		Settings::BLOCK_LENGTH_PIXEL / double(surface->h), 1));
	return present - 1;
}

Block *BlockRegistry::getRegistered(int id)
{
	if (id >= present) throw BadBlockType();
	return blocks[id];
}

Block *BlockRegistry::getRegistered(std::string name)
{
	if (map.find(name) == map.end()) throw BadBlockType();
	return blocks[map[name]];
}

void BlockRegistry::loadDebugTexture(ResourceLocation name_, Block *block)
{
	std::string name = name_;
	std::string filename = "assets/matrix/textures/block/debug.png";
	SDL_Surface *surface = tryLoadImage(filename);
	if (!surface) {
		g_logger->crash("Resource pack is damaged, failed to register %s",
			name.c_str());
	}
	block->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::BLOCK_LENGTH_PIXEL / double(surface->w),
		Settings::BLOCK_LENGTH_PIXEL / double(surface->h), 0));
}

namespace Blocks {
	int STONE;
	int DIRT;
	int GRASS_BLOCK;
};

void initBlock()
{
	static RegistryWrapper<BlockRegistry, Block> BLOCKS =
		RegistryWrapper<BlockRegistry, Block>::
		getWrapper(&blockRegistry, "matrix");
	Blocks::STONE = BLOCKS.registered("stone", new Block());
	Blocks::DIRT = BLOCKS.registered("dirt", new Block());
	Blocks::GRASS_BLOCK = BLOCKS.registered("grass_block", new Block());
}
