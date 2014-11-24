/*
 * A helper class that represents colours as three numbers and includes
 * a function to get the colour at a point within a gradient scale.
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

#ifndef COLOR_H
#define COLOR_H
#include <SDL.h>

// t is the type for components, u is the type for
// whole colors
template <typename t, typename u>
class Color
{
public:
	t r, g, b;

	Color(t red, t green, t blue) : r(red), g(green), b(blue) {}

	Color(u c, bool reversed = false)
	{
		if (!reversed)
		{
			r = (c >> 16) & 0xff;
			g = (c >> 8)  & 0xff;
			b = c         & 0xff;
		}
		else
		{
			r = c         & 0xff;
			g = (c >> 8)  & 0xff;
			b = (c >> 16) & 0xff;
		}
	}

	template <typename v, typename w>
	Color(Color<v, w> c) : r((t)c.r), g((t)c.g), b((t)c.b) {}

	inline u combine(bool reversed = false) { return !reversed ? ((u)r << 16) + ((u)g << 8) + (u)b : (u)r + ((u)g << 8) + ((u)b << 16); }

    typedef Color<short, long> color;

	static u gradientAt(double position, const int nColors, const u colors[], const double colorPositions[])
	{
		// find the color to start at
		int i = 0; for (; i < nColors && colorPositions[i] <= position; i++); i--;

		// can't start at a negative index
		if (i < 0) i = 0;
		// the color to end at
		int j = i + 1;
		// if i is outside the range of colors, both i and j should be the last color
		if (i >= nColors)
		{
			i = nColors - 1;
			j = i;
		}
		// if j is outside the range of colors, use the same as the starting color
		if (j >= nColors) j = i;

		// find the point between the two colors as a number between 0 and 1
		double x = i != j ? (position - colorPositions[i]) / (colorPositions[j] - colorPositions[i]) : 0;

		// calculate the color between
		color a = color(colors[i]);
		color b = color(colors[j]);
		color c = (b - a) * x + a;

		return c.combine(true);
	}

	inline Color operator+(Color c) { return Color(r + c.r, g + c.g, b + c.b); }
	inline Color operator-(Color c) { return Color(r - c.r, g - c.g, b - c.b); }

	template <typename v>
	Color (operator*)(v x) { return Color(r*x, g*x, b*x); }
	template <typename v>
	Color (operator/)(v x) { return Color(r/x, g/x, b/x); }
};

typedef Color<Uint8, Uint32> color;

#endif
