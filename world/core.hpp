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

#include <unordered_map>
#include <sstream>

struct BlockPos {
	long long x : 27;
	long long y : 10;
	long long z : 27;
	BlockPos() : x(0), y(0), z(0) {}
	BlockPos(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

struct SubChunkPos {
	int x, y, z;
	SubChunkPos() : x(0), y(0), z(0) {}
	SubChunkPos(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

struct ChunkPos {
	int x, z;
	ChunkPos() : x(0), z(0) {};
	ChunkPos(int x_, int z_) : x(x_), z(z_) {}
};

namespace DataTypes {
	const int BOOL = 0;
	const int CHAR = 1;
	const int SHORT = 2;
	const int INT = 3;
	const int LONGLONG = 4;
	const int FLOAT = 5;
	const int DOUBLE = 6;
	const int STRING = 7;
	const int ARRAY = 8;
	const int LIST = 9;
	const int COMPOUND = 10;
};

class ByteBuf {
	std::string buf;

public:
	void putBool(bool x);
	void putChar(char x);
	void putShort(short x);
	void putInt(int x);
	void putLonglong(long long x);
	void putFloat(float x);
	void putDouble(double x);
	void putString(std::string x);
	bool readBool();
	char readChar();
	short readShort();
	int readInt();
	long long readLonglong();
	float readFloat();
	double readDouble();
	std::string readString();
};

class Tag {
	static const int type = -1;

public:
	virtual void read(ByteBuf &buf) = 0;
	virtual void save(ByteBuf &buf) = 0;
};

class IntTag : public Tag {
protected:
	static const int type = DataTypes::INT;
	int i;

public:
	virtual void read(ByteBuf &buf);
	virtual void save(ByteBuf &buf);
	virtual int getValue();
	virtual void setValue(int x);
};

class CompoundTag : public Tag {
protected:
	static const int type = DataTypes::COMPOUND;
	std::unordered_map<std::string, Tag *> content;

public:
	CompoundTag() : content() {}
	virtual void read(ByteBuf &buf);
	virtual void save(ByteBuf &buf);
	virtual Tag *getValue(std::string key);
	virtual void setValue(std::string key, Tag *tag);
};

#endif
