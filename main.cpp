/*
 * main.cpp
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

#include <iostream>
#include "SDL.h"
#include "MandelbrotViewer.h"

// The width and height of the window
const int SCREEN_WIDTH			= 1024;
const int SCREEN_HEIGHT			= 800;

// The initial scale, x and y coordinates to render
const double START_SCALE		= 2.0;
const double START_X			= -0.5;
const double START_Y			= 0.0;

// The iteration depth to use at scale=1
const double DEPTH_1			= 100;
// The lower this is, the faster the iteration depth
// will increase as you zoom in.
const double DEPTH_SCALE_INDEX	= 3.4;

// Dragging the mouse from the bottom to the top of
// the screen will zoom in by this scale factor
const double SCALE_SPEED = 100;

void logSDLError(const char* msg)
{
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}


SDL_Texture* getPixelView(SDL_Renderer* ren)
{
	return SDL_CreateTexture(ren, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
}



int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError("SDL_Init");
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Mandelbrot Set", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		logSDLError("CreateWindow");
		return 1;
	}

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr)
	{
		logSDLError("CreateRenderer");
		return 1;
	}

	SDL_Texture* tex = getPixelView(ren);

	MandelbrotViewer viewer = MandelbrotViewer(SCREEN_WIDTH, SCREEN_HEIGHT, START_SCALE, START_X, START_Y,
		DEPTH_1, DEPTH_SCALE_INDEX, SCALE_SPEED);

    SDL_Event event;
	while (!viewer.done)
	{
		//events
		while (SDL_PollEvent(&event))
		{
			viewer.handleEvent(&event);
		}

		//process
		viewer.process();

		//draw
		Uint32* pix = viewer.renderPixels();
		SDL_UpdateTexture(tex, NULL, pix, SCREEN_WIDTH * sizeof(Uint32));
		delete[] pix;

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, viewer.getRenderTarget());
		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
