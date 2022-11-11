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

#ifndef __MATRIX_MATHS_HPP
#define __MATRIX_MATHS_HPP

#include <string>

class Vector2 {
	double x, y;

public:
	inline Vector2();
	inline Vector2(double x_, double y_);
	inline Vector2(const Vector2& vec);
};

namespace Maths {
	extern double _sin[360], _cos[360];
	int div(int x, int y);
	int mod(int x, int y);
	int sign(double x);
	double sin(int x);
	double cos(int x);
	float sqrt(float x);
	double sqrt(double x);
	float invsqrt(float x);
	double invsqrt(double x);
	unsigned long long chunkKey(int x, int z);
	char toChar(int x);
	std::string int2base10(int x);
	std::string int2base20(int x);
	std::string double2base10(double x, int w);
};

void initMaths();

#endif
