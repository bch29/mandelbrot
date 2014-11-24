/*
 * This ColorConverter simply returns different discrete colours based
 * on the value of x.
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

#ifndef BASICCONVERTER_H
#define BASICCONVERTER_H

#include "ColorConverter.h"

class BasicConverter : public ColorConverter
{
	const Uint32* colors;
	const double* colorPositions;
	const int nColors;

public:
	color convert(double x)
	{
		for (int i = nColors-1; i >= 0; i--)
		{
			if (x >= colorPositions[i])
				return color(colors[i]);
		}

		return colors[0];
	}

	BasicConverter(const Uint32* colors, const double* colorPositions, const int nColors) :
		colors(colors), colorPositions(colorPositions), nColors(nColors){};
};

#endif // BASICCONVERTER_H
