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

#include "noise.hpp"
#include "../functions.hpp"

#include <cmath>
#include <limits>

namespace Noises {

	double noise(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0 - ((n * (n * n * 15731 + 789221) +
			1376312589) & 0x7fffffff) / 1073741824.0);
	}

	double smoothedNoise(int x, int y)
	{
		double corners = (
			noise(x - 1, y - 1) +
			noise(x + 1, y - 1) +
			noise(x - 1, y + 1) +
			noise(x + 1, y + 1)) / 16;
		double sides = (
			noise(x - 1, y) +
			noise(x + 1, y) +
			noise(x, y - 1) +
			noise(x, y + 1)) / 8;
		double center = noise(x, y) / 4;
		return corners + sides + center;
	}

	double cosInterpolate(double a, double b, double x)
	{
		double ft = x * M_PI;
		double f = (1 - cos(ft)) * 0.5;
		return a * (1 - f) + b * f;
	}

	double interpolatedNoise(double x, double y)
	{
		int ix = int(x);
		int iy = int(y);
		double fx = x - ix;
		double fy = x - iy;
		double v1 = smoothedNoise(ix, iy);
		double v2 = smoothedNoise(ix + 1, iy);
		double v3 = smoothedNoise(ix, iy + 1);
		double v4 = smoothedNoise(ix + 1, iy + 1);
		double i1 = cosInterpolate(v1, v2, fx);
		double i2 = cosInterpolate(v3, v4, fx);
		return cosInterpolate(i1, i2, fy);
	}

	double perlinNoise(double x, double y)
	{
		double total = 0;
		double p = 0.5;
		int n = 4;
		for (int i = 0; i < n; i++) {
			int freq = 1 << i;
			double ampl = pow(p, i);
			total += interpolatedNoise(x * freq, y * freq) * ampl;
		}
		return total;
	}

};
