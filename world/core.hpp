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

#ifndef __WORLD_CORE_HPP
#define __WORLD_CORE_HPP

struct BlockPos {
	long long x : 27;
	long long y : 10;
	long long z : 27;
	BlockPos() : x(0), y(0), z(0) {}
	BlockPos(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

struct SubChunkPos {
	int x, y, z;
};

struct ChunkPos {
	int x, z;
};

#endif
