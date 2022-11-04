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

extern SDL_Window *g_window;
extern SDL_Surface *g_screen;
extern SDL_Renderer *g_renderer;
extern FPSmanager g_fpsManager;
extern Logger *g_logger;
extern Player *g_player;
extern bool g_isQuit;

#endif
