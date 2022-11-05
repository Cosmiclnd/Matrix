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

#include "level.hpp"
#include "../functions.hpp"
#include "../maths.hpp"

SubChunk::SubChunk(SubChunkPos pos_)
	: pos(pos_)
{
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				blocks[x][y][z] = -1;
			}
		}
	}
}

int SubChunk::getBlock(BlockPos pos_)
{
	BlockPos local = { Maths::mod(pos_.x, 16), Maths::mod(pos_.y, 16),
		Maths::mod(pos_.z, 16) };
	return blocks[local.x][local.y][local.z];
}

int SubChunk::getRelativeBlock(BlockPos pos_)
{
	return blocks[pos_.x][pos_.y][pos_.z];
}

void SubChunk::setBlock(BlockPos pos_, int block)
{
	BlockPos local = { Maths::mod(pos_.x, 16), Maths::mod(pos_.y, 16),
		Maths::mod(pos_.z, 16) };
	blocks[local.x][local.y][local.z] = block;
}

Chunk::Chunk(ChunkPos pos_)
	: pos(pos_), present(0)
{
	for (int i = 0; i < 64; i++) {
		map[i] = -1;
	}
}

SubChunk *Chunk::newSubChunk(int y)
{
	SubChunk *sub = getSubChunk(y);
	if (sub) return sub;
	map[y] = present++;
	SubChunkPos pos_ { pos.x, y, pos.z };
	sub = new SubChunk(pos_);
	subChunks.push_back(sub);
	return sub;
}

SubChunk *Chunk::getSubChunk(int y)
{
	for (int i = 0; i < present; i++) {
		if (map[y] == i) return subChunks[i];
	}
	return 0;
}

int Chunk::getBlock(BlockPos pos_)
{
	SubChunk *chunk = getSubChunk(Maths::div(pos_.y, 16));
	if (!chunk) return -1;
	return chunk->getBlock(pos_);
}

void Chunk::setBlock(BlockPos pos_, int block)
{
	SubChunk *chunk = newSubChunk(Maths::div(pos_.y, 16));
	chunk->setBlock(pos_, block);
}

int Level::getBlock(BlockPos pos)
{
	if (pos.y >= 1024 || pos.y < 0) return -1;
	ChunkPos cpos { Maths::div(pos.x, 16), Maths::div(pos.z, 16) };
	unsigned long long cpos_ = Maths::chunkKey(cpos.x, cpos.z);
	if (map.find(cpos_) == map.end()) return -1;
	Chunk *chunk = map[cpos_];
	return chunk->getBlock(pos);
}

void Level::setBlock(BlockPos pos, int block)
{
	ChunkPos cpos = { Maths::div(pos.x, 16), Maths::div(pos.z, 16) };
	Chunk *chunk = newChunk(cpos);
	chunk->setBlock(pos, block);
}

bool Level::existsChunk(ChunkPos pos)
{
	return map.find(Maths::chunkKey(pos.x, pos.z)) != map.end();
}

Chunk *Level::getChunk(ChunkPos pos)
{
	if (!existsChunk(pos)) return 0;
	return map[Maths::chunkKey(pos.x, pos.z)];
}

Chunk *Level::newChunk(ChunkPos pos)
{
	unsigned long long key = Maths::chunkKey(pos.x, pos.z);
	if (!existsChunk(pos)) map[key] = new Chunk(pos);
	Chunk *chunk = map[key];
	return chunk;
}

namespace Levels {
	Level *OVERWORLD = (new Level())->setGravity(0.05);
};
