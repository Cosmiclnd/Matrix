#ifndef __MATRIX_MATHS_HPP
#define __MATRIX_MATHS_HPP

#include <string>

namespace Maths {
	extern double _sin[360], _cos[360];
	int div(int x, int y);
	int mod(int x, int y);
	int sign(double x);
	double sin(int x);
	double cos(int x);
	unsigned long long chunkKey(int x, int z);
	char toChar(int x);
	std::string int2base10(int x);
	std::string int2base20(int x);
	std::string double2base10(double x, int w);
};

void initMaths();

#endif
