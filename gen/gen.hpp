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

#ifndef __GEN_GEN_HPP
#define __GEN_GEN_HPP

#include "../world/level.hpp"

#include <unordered_map>
#include <thread>
#include <list>

class ChunkLoader {
	Level *level;
	int seed;
	std::unordered_map<long long, bool> map;

public:
	ChunkLoader() : level(0), seed(0) {}
	Level *getLevel() { return level; }
	void setLevel(Level *level_) { level = level_; }
	void setSeed(int seed_) { seed = seed_; }
	bool isLoaded(ChunkPos pos);
	void startLoad(ChunkPos pos);
	void nowLoad(ChunkPos pos);
};

extern ChunkLoader g_chunkLoader;

#endif
