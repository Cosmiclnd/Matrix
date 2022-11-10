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

#include "functions.hpp"
#include "settings.hpp"
#include "gui/screen.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <ctime>

SDL_Window *g_window;
SDL_Surface *g_screen;
SDL_Renderer *g_renderer;
FPSmanager g_fpsManager;
Logger *g_logger;
Player *g_player;
bool g_isQuit = false;

void error(std::string msg)
{
	std::cerr << "Matrix: " << msg;
	exit(1);
}

void init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) error("failed to initalize SDL2");
	IMG_Init(~0);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	g_window = SDL_CreateWindow("Matrix", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, Settings::WINDOW_WIDTH,
		Settings::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!g_window) error("failed to create window");
	g_screen = SDL_GetWindowSurface(g_window);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	SDL_initFramerate(&g_fpsManager);
	SDL_setFramerate(&g_fpsManager, Settings::FPS);
	g_logger = new Logger();
	g_player = new Player();
	time_t now = time(0);
	char *s = ctime(&now);
	s[strlen(s) - 1] = 0;  // skip '\n' at the end of the line
	g_logger->info("Matrix started at %s", s);
}

void quit()
{
	g_isQuit = true;
	SDL_DestroyRenderer(g_renderer);
	SDL_FreeSurface(g_screen);
	SDL_DestroyWindow(g_window);
	IMG_Quit();
	SDL_Quit();
	exit(0);
}

SDL_Surface *tryLoadImage(std::string path, bool error)
{
	std::string filename = std::string(SDL_GetBasePath() + path);
	if (!std::filesystem::exists(filename)) {
		if (error)
			g_logger->error("File not found: %s", filename.c_str());
		return 0;
	}
	SDL_Surface *image = IMG_Load(filename.c_str());
	if (!image) {
		if (error)
			g_logger->error("Failed to load texture: %s", filename.c_str());
		return 0;
	}
	return image;
}

SDL_Surface *forceLoadImage(std::string path, bool error)
{
	SDL_Surface *surface = tryLoadImage(path, error);
	if (!surface) {
		g_logger->crash("Can't load texture. \n  forceLoadImage() failed.");
	}
	return surface;
}
