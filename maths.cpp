#include "maths.hpp"

#include <cmath>
#include <sstream>

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

	unsigned long long chunkKey(int x, int z)
	{
		return (unsigned long long) x << 32 | (unsigned int) z;
	}

	double sin(int x)
	{
		return _sin[x];
	}

	double cos(int x)
	{
		return _cos[x];
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
