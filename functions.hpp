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

#ifndef __MATRIX_FUNCTIONS_HPP
#define __MATRIX_FUNCTIONS_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>

#include "registry.hpp"
#include "entity/entity.hpp"

void error(std::string msg);
void init();
void quit();

SDL_Surface *tryLoadImage(std::string path);
SDL_Surface *forceLoadImage(std::string path);

extern SDL_Window *g_window;
extern SDL_Surface *g_screen;
extern SDL_Renderer *g_renderer;
extern FPSmanager g_fpsManager;
extern Logger *g_logger;
extern Player *g_player;
extern bool g_isQuit;

#endif
