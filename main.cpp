#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <thread>

#include "functions.hpp"
#include "maths.hpp"
#include "hook.hpp"
#include "entity/entity.hpp"
#include "world/level.hpp"
#include "world/tick.hpp"
#include "gui/font.hpp"

int Settings::FPS = 60;

void initAll()
{
	init();
	initBlock();
	initHook();
	initScreen();
	initMaths();
	initEntity();
	initFont();
}

int main()
{
	initAll();
	g_player->setLevel(Levels::OVERWORLD);
	g_player->teleport(0, 91, 0);
	g_player->pushGuiLayer(
		new GuiLayer(makeNewScreen<WorldScreen>(Screens::WORLD, g_player)));
	for (int i = -10; i <= 80; i++) {
		for (int j = 0; j <= 90; j++) {
			for (int k = -80; k <= 80; k++) {
				Levels::OVERWORLD->setBlock(BlockPos(i, j, k), Blocks::STONE);
			}
		}
	}
	Levels::OVERWORLD->setBlock(BlockPos(2, 91, 2), Blocks::STONE);
	Levels::OVERWORLD->setBlock(BlockPos(2, 92, 3), Blocks::STONE);
	Levels::OVERWORLD->setBlock(BlockPos(2, 93, 4), Blocks::DIRT);
	Levels::OVERWORLD->setBlock(BlockPos(2, 94, 5), Blocks::GRASS_BLOCK);
	std::thread threadTickUpdater(funcTickUpdater);
	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		else {
			g_player->updateEvent(&event);
		}
		g_player->updateScreen();
		SDL_UpdateWindowSurface(g_window);
		SDL_RenderPresent(g_renderer);
		SDL_framerateDelay(&g_fpsManager);
	}
	g_player->popGuiLayer();
	quit();
	return 0;
}
