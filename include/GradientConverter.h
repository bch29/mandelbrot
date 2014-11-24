/*
 * This ColorConverter uses a gradient scale.
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

#ifndef GRADIENTCONVERTER_H
#define GRADIENTCONVERTER_H

#include "ColorConverter.h"
class GradientConverter : public ColorConverter
{
	const Uint32* colors;
	const double* colorPositions;
	const int nColors;

public:
	inline color convert(double x)
	{
		return color::gradientAt(x, nColors, colors, colorPositions);
	}

	GradientConverter(const Uint32* colors, const double* colorPositions, const int nColors) :
		colors(colors), colorPositions(colorPositions), nColors(nColors){};
};

#endif
