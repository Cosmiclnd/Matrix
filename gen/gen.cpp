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

#include "gen.hpp"
#include "noise.hpp"
#include "../maths.hpp"
#include "../functions.hpp"
#include "../world/block.hpp"

ChunkLoader g_chunkLoader;

static void funcChunkLoader(Chunk *chunk, int seed)
{
	ChunkPos cpos = chunk->getPos();
	double x, y;
	for (int i = 0; i < 16; i++) {
		for (int k = 0; k < 16; k++) {
			x = ((cpos.x << 4) + i) * 0.125;
			y = ((cpos.z << 4) + k) * 0.125;
			int h = 64 + round(Noises::perlinNoise(x, y) * 5 - 4);
			for (int j = 0; j < h - 3; j++) {
				chunk->setBlock(BlockPos(
					(cpos.x << 4) + i,
					j,
					(cpos.z << 4) + k),
					Blocks::STONE);
			}
			for (int j = h - 3; j < h; j++) {
				chunk->setBlock(BlockPos(
					(cpos.x << 4) + i,
					j,
					(cpos.z << 4) + k),
					Blocks::DIRT);
			}
			chunk->setBlock(BlockPos(
				(cpos.x << 4) + i,
				h,
				(cpos.z << 4) + k),
				Blocks::GRASS_BLOCK);
			
		}
	}
}

void ChunkLoader::setLoaded(ChunkPos pos)
{
	unsigned long long key = Maths::chunkKey(pos.x, pos.z);
	map[key] = true;
}

bool ChunkLoader::isLoaded(ChunkPos pos)
{
	unsigned long long key = Maths::chunkKey(pos.x, pos.z);
	if (map.find(key) == map.end()) return false;
	return map[key];
}

void ChunkLoader::startLoad(ChunkPos pos)
{
	Chunk *chunk = level->newChunk(pos);
	std::thread threadChunkLoader(funcChunkLoader, chunk, seed);
	threadChunkLoader.detach();
}

void ChunkLoader::nowLoad(ChunkPos pos)
{
	Chunk *chunk = level->newChunk(pos);
	funcChunkLoader(chunk, seed);
}
