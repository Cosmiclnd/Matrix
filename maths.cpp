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

#include "maths.hpp"

#include <cmath>
#include <sstream>
#include <algorithm>

static unsigned int BIT_HASH1 = 0x85297a4d;
static unsigned int BIT_HASH2 = 0x68e31da4;
static unsigned int BIT_HASH3 = 0x1b56cae9;

namespace Maths {

	int div(int x, int y)
	{
		int r = x / y;
		return x < 0 && x % y != 0 ? r - 1 : r;
	}

	int mod(int x, int y)
	{
		int r = x % y;
		return r < 0 ? r + y : r;
	}

	int sign(double x)
	{
		return x < 0 ? -1 : (x > 0 ? 1 : 0);
	}

	double sin(int x)
	{
		return _sin[x];
	}

	double cos(int x)
	{
		return _cos[x];
	}

	float sqrt(float x)
	{
		return 1.0f / invsqrt(x);
	}

	double sqrt(double x)
	{
		return 1.0 / invsqrt(x);
	}

	float invsqrt(float x)
	{
		int i;
		float x2;
		x2 = x * 0.5;
		i = *(int *) &x;
		i = 0x5f375a86 - (i >> 1);
		x = *(float *) &i;
		x = x * (1.5f - (x2 * x * x));
		x = x * (1.5f - (x2 * x * x));
		x = x * (1.5f - (x2 * x * x));
		return x;
	}

	double invsqrt(double x)
	{
		long long i;
		double x2;
		x2 = x * 0.5;
		i = *(long long *) &x;
		i = 0x5fe68e93c3ddae18 - (i >> 1);
		x = *(double *) &i;
		x = x * (1.5 - (x2 * x * x));
		x = x * (1.5 - (x2 * x * x));
		x = x * (1.5 - (x2 * x * x));
		return x;
	}

	unsigned long long chunkKey(int x, int z)
	{
		return (unsigned long long) x << 32 | (unsigned int) z;
	}

	char toChar(int x)
	{
		return x >= 10 ? 'a' + x - 10 : '0' + x;
	}

	std::string int2base10(int x)
	{
		return std::to_string(x);
	}

	std::string int2base20(int x)
	{
		std::string s;
		do {
			s = std::string("$") + toChar(x % 20) + s;
			x /= 20;
		}
		while (x > 0);
		return s;
	}

	std::string double2base10(double x, int w)
	{
		std::stringstream ss;
		ss.precision(w);
		ss << std::fixed << x;
		std::string s;
		ss >> s;
		return s;
	}

	double _sin[360], _cos[360];
};

void initMaths()
{
	for (int i = 0; i < 360; i++) {
		Maths::_cos[i] = cos(i);
		Maths::_sin[i] = sin(i);
	}
}
