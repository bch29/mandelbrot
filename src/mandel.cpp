/*
 * `mandelbrot` is the function which generates the mandelbrot set itself
 * by returning a measure of the speed of divergence at each pixel. This
 * is given by taking the number of iterations it takes for the modulus of
 * z to become greater than an arbitrary real number and dividing this by
 * the maximum number of iterations, given by `depth`.
 *
 * If the algorithm reaches the maximum number of iterations before mod z
 * becomes greater than the arbitrary number, the mandelbrot equation is
 * assumed to be convergent at that pixel and 0 is returned.
 *
 * Copyright (C) 2013 Bradley Hardy
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "mandel.h"
#include "SDL.h"

double** mandelbrot(int width, int height, double xcent, double ycent, double scale, int depth)
{
	double ascale = scale / width;
	double xmin = xcent - (width / 2) * ascale;
	double ymax = ycent + (height / 2) * ascale;

	double** out = new double*[width];

	for (int i = 0; i < width; i++)
	{
        out[i] = new double[height];
		double a = xmin + i * ascale;

		for (int j = 0; j < height; j++)
		{
			double b = ymax - j * ascale;
			double x = 0;
			double y = 0;

            // Iterating to find the rate of divergence of the
            // mandelbrot equation at pixel (i, j).
			for (int h = 0; h < depth; h++)
			{
				double xnew = x*x-y*y + a;
				y = 2*x*y + b;
				x = xnew;

				if (x*x + y*y > height) {
                    out[i][j] = ((double)h) / depth;
					break;
                }
			}
		}
	}

	return out;
}

double** mandel1(int width, int height) { return mandelbrot(width, height, -0.765, 0, 2.5, 0x20); }
double** mandel2(int width, int height) { return mandelbrot(width, height, -1.775, 0, 0.05, 0x80); }

double** mandel(int width, int height) { return mandel1(width, height); }
