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
#include "../maths.hpp"
#include "../functions.hpp"
#include "../world/block.hpp"

ChunkLoader g_chunkLoader;

static void funcChunkLoader(Chunk *chunk, int seed)
{
	ChunkPos cpos = chunk->getPos();
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			chunk->setBlock(BlockPos(
				(cpos.x << 4) + i,
				90,
				(cpos.z << 4) + j),
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
