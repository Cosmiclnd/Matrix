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
