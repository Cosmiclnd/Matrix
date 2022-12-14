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
public:
	double x, y;

	inline Vector2();
	inline Vector2(double x_, double y_);

	inline Vector2 operator-();
	inline Vector2 operator+(const Vector2 &vec);
	inline Vector2 operator-(const Vector2 &vec);
	inline Vector2 operator*(double a);
	inline Vector2 operator*(const Vector2 &vec);
	inline Vector2 operator/(double a);
	inline Vector2 operator/(const Vector2 &vec);

	inline double length();
	inline double dot(const Vector2 &vec);
	inline void normalize();
	inline void zero();
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

Vector2::Vector2()
	: x(0), y(0)
{}

Vector2::Vector2(double x_, double y_)
	: x(x_), y(y_)
{}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 &vec)
{
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2 &vec)
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator*(double a)
{
	return Vector2(x * a, y * a);
}

Vector2 Vector2::operator*(const Vector2 &vec)
{
	return Vector2(x * vec.x, y * vec.y);
}

Vector2 Vector2::operator/(double a)
{
	return Vector2(x / a, y / a);
}

Vector2 Vector2::operator/(const Vector2 &vec)
{
	return Vector2(x / vec.x, y / vec.y);
}

double Vector2::length()
{
	return Maths::sqrt(x * x + y * y);
}

double Vector2::dot(const Vector2 &vec)
{
	return x * vec.x + y * vec.y;
}

void Vector2::normalize()
{
	double mg = x * x + y * y;
	if (mg >= 0) {
		double rs = Maths::invsqrt(mg);
		x *= rs;
		y += rs;
	}
}

#endif
