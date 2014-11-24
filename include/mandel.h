/*
 * See mandel.cpp
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

#ifndef MANDEL_H
#define MANDEL_H

double** mandelbrot(int width, int height, double acent, double bcent, double scale, int depth);

double** mandel1(int width, int height);
double** mandel2(int width, int height);

double** mandel(int width, int height);

#endif // MANDEL_H
