/*
 * See MandelbrotViewer.h
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

#include "MandelbrotViewer.h"
#include "Color.h"

double** MandelbrotViewer::getSet(int width, int height, double x, double y, double scale)
{
    int depth = (int)pow(depthScaling / scale, 1.0 / depthScaleIndex);
    double** newSet = mandelbrot(width, height, x, y, scale, depth);
    printf("X: %f Y: %f scale: %f\n", x, y, scale);
	return newSet;
}

MandelbrotViewer::MandelbrotViewer(const Uint32 colors[], const double colorPositions[], const int nColors,
			int screenWidth, int screenHeight, double startScale, double startX, double startY,
			double depth1, double depthScaleIndex, double scaleSpeed) :
			Viewer(screenWidth, screenHeight, startScale, startX, startY, scaleSpeed), converter(colors, colorPositions, nColors)
          , depthScaleIndex(depthScaleIndex)
{
	depthScaling = pow(depth1, depthScaleIndex);

	done = false;
	x = startX;
	y = startY;
	scale = startScale;
	set = getSet(screenWidth, screenHeight, x, y, scale);
	setChanged = false;
	pixelsDrawn = false;

	rclickx = 0;
	rclicky = 0;
	lclickx = 0;
	lclicky = 0;

	isRight = false;
	isLeft = false;
}


void MandelbrotViewer::handleEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == 3)
		{
			SDL_GetMouseState(&rclickx, &rclicky);
			isRight = true;
		}
		else if (event->button.button == 1)
		{
			SDL_GetMouseState(&lclickx, &lclicky);
			isLeft = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == 3)
		{
			setChanged = true;
			isRight = false;

			int mousex, mousey;
			SDL_GetMouseState(&mousex, &mousey);
			x -= (mousex - rclickx) * (scale / screenWidth);
			y += (mousey - rclicky) * (scale / screenWidth);
		}
		else if (event->button.button == 1)
		{
			setChanged = true;
			isLeft = false;

			int mousex, mousey;
			SDL_GetMouseState(&mousex, &mousey);
			double scaleChange = pow(scaleSpeed, (mousey - lclicky) / ((double)screenHeight));
			scale /= scaleChange;
		}
		break;
	case SDL_QUIT:
		done = true;
		break;
	}
}


void MandelbrotViewer::process()
{
	int mousex, mousey;
	SDL_GetMouseState(&mousex, &mousey);

	if (setChanged)
	{
        printf("Recalculating...\n");
		delete[] set;
		set = getSet(screenWidth, screenHeight, x, y, scale);

		setChanged = false;
		pixelsDrawn = false;
	}

	int xmove = 0;
	int ymove = 0;
	int width = screenWidth;
	int height = screenHeight;

	if (isRight)
	{
		xmove = mousex - rclickx;
		ymove = mousey - rclicky;
	}

	if (isLeft)
	{
		double scaleChange = pow(scaleSpeed, (mousey - lclicky) / ((double)screenHeight));
		width *= scaleChange;
		height *= scaleChange;
	}

	target.w = width;
	target.h = height;
	target.x = xmove + (screenWidth - width) / 2;
	target.y = ymove + (screenHeight - height) / 2;
}

Uint32* MandelbrotViewer::renderPixels()
{
	if (!pixelsDrawn)
		pixels = arrayToPixels(set, screenWidth, screenHeight, converter);
	return pixels;
}
