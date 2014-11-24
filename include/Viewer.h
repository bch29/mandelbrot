/*
 * An abstract class for an SDL direct-pixel renderer.
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

#ifndef VIEWER_H
#define VIEWER_H

#include <SDL.h>
#include "ColorConverter.h"

class Viewer
{
public:
	int screenWidth;
	int screenHeight;

	double scaleSpeed;
	double x, y, scale;
	Uint32* pixels;
	bool setChanged;
	bool pixelsDrawn;

	int rclickx;
	int rclicky;
	int lclickx;
	int lclicky;

	bool isRight;
	bool isLeft;

	SDL_Rect target;

	bool done;

	virtual void handleEvent(SDL_Event* event) = 0;
	virtual void process() = 0;
	virtual Uint32* renderPixels() = 0;
	virtual SDL_Rect* getRenderTarget() { return &target; };

	Viewer(int screenWidth, int screenHeight, double startScale, double startX, double startY, double scaleSpeed);

protected:
	static Uint32* arrayToPixels(double** set, int width, int height, ColorConverter& converter)
	{
		Uint32* pixels = new Uint32[width * height];

		for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                pixels[y * width + x] = converter.convert(set[x][y]).combine(true);

		return pixels;
	}
};

#endif
