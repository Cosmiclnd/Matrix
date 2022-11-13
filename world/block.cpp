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

#include "block.hpp"
#include "../functions.hpp"
#include "../maths.hpp"
#include "item.hpp"

#include <filesystem>
#include <unordered_map>
#include <SDL2/SDL2_rotozoom.h>

BlockRegistry blockRegistry;

Block::Block()
{
	for (int i = 0; i < Settings::BLOCK_LENGTH_PIXEL; i++) {
		for (int j = 0; j < Settings::BLOCK_LENGTH_PIXEL; j++) {
			mask[i][j] = true;
		}
	}
}

SDL_Surface *Block::getSurface(BlockPos pos)
{
	return surface;
}

void Block::setSurface(SDL_Surface *surface_)
{
	surface = surface_;
}

SDL_Surface *RandomTextureBlock::getSurface(BlockPos pos)
{
	srand(int((pos.x << 24) + (pos.y << 14) + pos.z));
	return extended[Maths::mod(rand(), 4)];
}

void RandomTextureBlock::setSurface(SDL_Surface *surface_)
{
	extended[0] = surface_;
	extended[1] = rotateSurface90Degrees(surface_, 1);
	extended[2] = rotateSurface90Degrees(surface_, 2);
	extended[3] = rotateSurface90Degrees(surface_, 3);
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
		g_logger->warn("Loading debug texture instead");
		loadDebugTexture(name_, block);
		return present - 1;
	}
	block->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::BLOCK_LENGTH_PIXEL / double(surface->w),
		Settings::BLOCK_LENGTH_PIXEL / double(surface->h), 1));
	block->setItemId(itemRegistry.registered(
		name_, new BlockItem(Item::Properties(), present - 1)));
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
	SDL_Surface *surface = forceLoadImage(filename);
	block->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::BLOCK_LENGTH_PIXEL / double(surface->w),
		Settings::BLOCK_LENGTH_PIXEL / double(surface->h), 0));
}

namespace Blocks {
	int STONE;
	int BEDROCK;
	int DIRT;
	int GRASS_BLOCK;
};

void initBlock()
{
	static RegistryWrapper<BlockRegistry, Block *> BLOCKS =
		RegistryWrapper<BlockRegistry, Block *>::
		getWrapper(&blockRegistry, "matrix");
	Blocks::STONE = BLOCKS.registered("stone",
		(new RandomTextureBlock())->setHardness(3.0));
	Blocks::BEDROCK = BLOCKS.registered("bedrock",
		(new Block())->setHardness(-1));
	Blocks::DIRT = BLOCKS.registered("dirt", (new Block())->setHardness(0.5));
	Blocks::GRASS_BLOCK = BLOCKS.registered("grass_block",
		(new Block())->setHardness(0.5));
}
