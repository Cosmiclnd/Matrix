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

#ifndef __WORLD_LEVEL_HPP
#define __WORLD_LEVEL_HPP

#include "core.hpp"
#include "block.hpp"

#include <vector>
#include <unordered_map>

class SubChunk {
	SubChunkPos pos;
	int blocks[16][16][16];

public:
	SubChunk(SubChunkPos pos_);
	int getBlock(BlockPos pos_);
	int getRelativeBlock(BlockPos pos_);
	void setBlock(BlockPos pos_, int block);
};

class Chunk {
	ChunkPos pos;
	char map[64], present;
	std::vector<SubChunk *> subChunks;

public:
	Chunk(ChunkPos pos_);
	SubChunk *newSubChunk(int y);
	SubChunk *getSubChunk(int y);
	int getBlock(BlockPos pos_);
	void setBlock(BlockPos pos_, int block);
};

class Level {
	std::unordered_map<unsigned long long, Chunk *> map;
	double gravity;

public:
	int getBlock(BlockPos pos);
	double getGravity() { return gravity; }
	void setBlock(BlockPos pos, int block);
	Level *setGravity(double gravity_) { gravity = gravity_; return this; }
	bool existsChunk(ChunkPos pos);
	Chunk *getChunk(ChunkPos pos);
};

namespace Levels {
	extern Level *OVERWORLD;
};

#endif
