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

#include "core.hpp"

void ByteBuf::putBool(bool x)
{
	buf.push_back(char(x));
}

void ByteBuf::putChar(char x)
{
	buf.push_back(x);
}

void ByteBuf::putShort(short x_)
{
	unsigned short x = *(unsigned short *) &x_;
	char x1 = x & 0xff;
	char x2 = (x >> 8) & 0xff;
	buf.append({ x1, x2 });
}

void ByteBuf::putInt(int x_)
{
	unsigned int x = *(unsigned int *) &x_;
	char x1 = x & 0xff;
	char x2 = (x >> 8) & 0xff;
	char x3 = (x >> 16) & 0xff;
	char x4 = (x >> 24) & 0xff;
	buf.append({ x1, x2, x3, x4 });
}

void ByteBuf::putLonglong(long long x_)
{
	unsigned long long x = *(unsigned long long *) &x_;
	char x1 = x & 0xff;
	char x2 = (x >> 8) & 0xff;
	char x3 = (x >> 16) & 0xff;
	char x4 = (x >> 24) & 0xff;
	char x5 = (x >> 32) & 0xff;
	char x6 = (x >> 40) & 0xff;
	char x7 = (x >> 48) & 0xff;
	char x8 = (x >> 56) & 0xff;
	buf.append({ x1, x2, x3, x4, x5, x6, x7, x8 });
}

void ByteBuf::putFloat(float x_)
{
	int x = *(int *) &x_;
	putInt(x);
}

void ByteBuf::putDouble(double x_)
{
	long long x = *(long long *) &x_;
	putLonglong(x);
}

void ByteBuf::putString(std::string x)
{
	buf.append(x).push_back(0);
}

bool ByteBuf::readBool()
{
	if (buf.size() < 1) return false;
	char c = buf.front();
	buf.erase(0, 1);
	buf.shrink_to_fit();
	return c != 0;
}

char ByteBuf::readChar()
{
	if (buf.size() < 1) return 0;
	char c = buf.front();
	buf.erase(0, 1);
	buf.shrink_to_fit();
	return c;
}

short ByteBuf::readShort()
{
	if (buf.size() < 2) return 0;
	unsigned short x = 0;
	x |= ((unsigned short) buf[0] & 0xff);
	x |= ((unsigned short) buf[1] & 0xff) << 8;
	buf.erase(0, 2);
	buf.shrink_to_fit();
	short x_ = *(short *) &x;
	return x_;
}

int ByteBuf::readInt()
{
	if (buf.size() < 4) return 0;
	unsigned int x = 0;
	x |= ((unsigned int) buf[0] & 0xff);
	x |= ((unsigned int) buf[1] & 0xff) << 8;
	x |= ((unsigned int) buf[2] & 0xff) << 16;
	x |= ((unsigned int) buf[3] & 0xff) << 24;
	buf.erase(0, 4);
	buf.shrink_to_fit();
	int x_ = *(int *) &x;
	return x_;
}

long long ByteBuf::readLonglong()
{
	if (buf.size() < 8) return 0;
	unsigned long long x = 0;
	x |= ((unsigned long long) buf[0] & 0xff);
	x |= ((unsigned long long) buf[1] & 0xff) << 8;
	x |= ((unsigned long long) buf[2] & 0xff) << 16;
	x |= ((unsigned long long) buf[3] & 0xff) << 24;
	x |= ((unsigned long long) buf[4] & 0xff) << 32;
	x |= ((unsigned long long) buf[5] & 0xff) << 40;
	x |= ((unsigned long long) buf[6] & 0xff) << 48;
	x |= ((unsigned long long) buf[7] & 0xff) << 56;
	buf.erase(0, 8);
	buf.shrink_to_fit();
	long long x_ = *(long long *) &x;
	return x_;
}

float ByteBuf::readFloat()
{
	int x = readInt();
	float x_ = *(float *) & x;
	return x_;
}

double ByteBuf::readDouble()
{
	long long x = readLonglong();
	double x_ = *(double *) &x;
	return x_;
}

std::string ByteBuf::readString()
{
	std::string s;
	int i = 0;
	for (; buf[i] != 0 && i < buf.size(); i++) {
		s += buf[i];
	}
	buf.erase(0, i);
	if (buf[0] == 0) buf.erase(0, 1);
	buf.shrink_to_fit();
	return s;
}

static Tag *readNewTag(ByteBuf &buf)
{
	Tag *tag = 0;
	int t = buf.readInt();
	switch (t) {
		case DataTypes::INT:
		{
			tag = new IntTag();
			break;
		}
		case DataTypes::COMPOUND:
		{
			tag = new CompoundTag();
			break;
		}
	}
	tag->read(buf);
	return tag;
}

void IntTag::read(ByteBuf &buf)
{
	i = buf.readInt();
}

void IntTag::save(ByteBuf &buf)
{
	buf.putInt(DataTypes::INT);
	buf.putInt(i);
}

int IntTag::getValue()
{
	return i;
}

void IntTag::setValue(int x)
{
	i = x;
}

void CompoundTag::read(ByteBuf &buf)
{
	int size = buf.readInt();
	for (int i = 0; i < size; i++) {
		std::string s = buf.readString();
		Tag *tag = readNewTag(buf);
		content[s] = tag;
	}
}

void CompoundTag::save(ByteBuf &buf)
{
	buf.putInt(DataTypes::COMPOUND);
	buf.putInt(content.size());
	for (auto it = content.begin(); it != content.end(); it++) {
		std::pair<std::string, Tag *> pair = *it;
		buf.putString(pair.first);
		pair.second->save(buf);
	}
}

Tag *CompoundTag::getValue(std::string key)
{
	if (content.find(key) == content.end()) return 0;
	return content[key];
}

void CompoundTag::setValue(std::string key, Tag *tag)
{
	content[key] = tag;
}
