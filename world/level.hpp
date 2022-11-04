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
