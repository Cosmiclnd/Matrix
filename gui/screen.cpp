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

#include "screen.hpp"
#include "font.hpp"
#include "../functions.hpp"
#include "../maths.hpp"
#include "../entity/entity.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm>

ScreenRegistry screenRegistry;

Screen::Screen(int x_, int y_, int w_, int h_)
{
	surface = SDL_CreateRGBSurface(0, w_, h_, 32, 0, 0, 0, 0);
	renderer = SDL_CreateSoftwareRenderer(surface);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
}

Screen::~Screen()
{
	SDL_FreeSurface(surface);
}

void Screen::update(bool show)
{
	if (show) {
		SDL_Rect rect {0, 0, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT};
		SDL_BlitSurface(surface, 0, g_screen, &rect);
		SDL_RenderClear(renderer);
	}
}

Screen *Screen::make(void *player_)
{
	return new Screen(0, 0, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
}

StartScreen::StartScreen(int x_, int y_, int w_, int h_)
	: Screen(x_, y_, w_, h_)
{}

void StartScreen::update(bool show)
{
	if (show) {
		SDL_FillRect(surface, 0, 0xffffffff);
	}
	Screen::update(show);
}

StartScreen *StartScreen::make(void *player_)
{
	return new StartScreen(0, 0,
		Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
}

WorldScreen::WorldScreen(int x_, int y_, int w_, int h_)
	: Screen(x_, y_, w_, h_), fps(0), showingFps(0), lastShowFps()
{}

void WorldScreen::update(bool show)
{
	if (show) {
		SDL_FillRect(surface, 0, 0xff00afff);
		showPlayerScene();
		showFps();
		showPos();
	}
	Screen::update(show);
}

WorldScreen *WorldScreen::make(void *player_)
{
	return new WorldScreen(
		0, 0, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
}

void WorldScreen::showSubChunk(Chunk *chunk, SubChunk *subChunk, int x, int y,
	int z, double px, double py, double pz)
{
	int maxj = py - (y << 4) + 2;
	maxj = maxj < 16 ? maxj : 16;
	for (int i = 0; i < 16; i++) {
		for (int k = 0; k < 16; k++) {
			int j = std::min(
				int(round(py + 2)), ((y + 1) << 4) - 1) - (y << 4);
			if (j < 0) continue;
			j %= 16;
			BlockPos rpos = { i, j, k };
			for (; j >= 0; j--) {
				rpos.y = j;
				if (subChunk->getRelativeBlock(rpos) != -1) {
					break;
				}
			}
			int block = subChunk->getRelativeBlock(rpos);
			if (block == -1) continue;
			BlockPos pos = { i + (x << 4), j + (y << 4), k + (z << 4) };
			SDL_Rect rect = {
				int((px - pos.x) * Settings::BLOCK_LENGTH_PIXEL +
					Settings::WINDOW_WIDTH / 2),
				int((pz - pos.z) * Settings::BLOCK_LENGTH_PIXEL +
					Settings::WINDOW_HEIGHT / 2),
				Settings::BLOCK_LENGTH_PIXEL,
				Settings::BLOCK_LENGTH_PIXEL
			};
			SDL_BlitSurface(blockRegistry.getRegistered(block)->
					getSurface(pos), 0, surface, &rect);
			int color, alpha;
			if (py < pos.y) color = 255;
			else color = 0;
			alpha = round(abs((py - pos.y) * 27));
			if (alpha > 255) alpha = 255;
			SDL_SetRenderDrawColor(renderer, color, color, color, alpha);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void WorldScreen::showPlayerScene()
{
	double px = round(g_player->getX() * 100) / 100;
	double py = round(g_player->getY() * 100) / 100;
	double pz = round(g_player->getZ() * 100) / 100;
	int startw = Maths::div(px, 16) - Settings::CHUNKS_SHOWW / 2;
	int starth = Maths::div(pz, 16) - Settings::CHUNKS_SHOWH / 2;
	Level *level = g_player->getLevel();
	int maxy = Maths::div(py, 16) + 1;
	for (int x = startw; x < startw + Settings::CHUNKS_SHOWW; x++) {
		for (int z = starth; z < starth + Settings::CHUNKS_SHOWH; z++) {
			ChunkPos cpos { x, z };
			Chunk *chunk = level->getChunk(cpos);
			if (!chunk) continue;
			for (int y = 0; y < maxy; y++) {
				SubChunk *subChunk = chunk->getSubChunk(y);
				if (!subChunk) continue;
				showSubChunk(chunk, subChunk, x, y, z, px, py, pz);
			}
		}
	}
	SDL_Rect rect {
		Settings::WINDOW_WIDTH / 2 - 8,
		Settings::WINDOW_HEIGHT / 2 - 8,
		16, 16};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 160);
	SDL_RenderDrawRect(renderer, &rect);
}

void WorldScreen::showPos()
{
	static FontStyle style = { 0xffffffff, 0x00000000, 16 };
	static SDL_Rect rect = { 1, 1, 0, 0 };
	g_ascii.setStyle(style)->setString(
		Maths::double2base10(g_player->getX(), 2) + " " +
		Maths::double2base10(g_player->getY(), 2) + " " +
		Maths::double2base10(g_player->getZ(), 2))->blit(surface, &rect);
}

void WorldScreen::showFps()
{
	static FontStyle style = { 0xffffffff, 0x00000000, 16 };
	static SDL_Rect rect = { 1, 17, 0, 0 };
	fps++;
	std::chrono::high_resolution_clock::time_point current =
		std::chrono::high_resolution_clock::now();
	g_ascii.setStyle(style)->
		setString("FPS: " + Maths::int2base10(showingFps) + "/" +
		Maths::int2base10(Settings::FPS))-> blit(surface, &rect);
	if (current - lastShowFps >= std::chrono::seconds(1)) {
		lastShowFps = current;
		showingFps = fps;
		fps = 0;
	}
}

ScreenRegistry::ScreenRegistry()
	: present(0)
{
	for (int i = 0; i < Settings::MAX_SCREENS; i++) {
		screens[i] = 0;
	}
}

int ScreenRegistry::registered(ResourceLocation name_, Screen *screen)
{
	std::string name = name_;
	if (map.find(name) != map.end()) throw AmbigousScreenError();
	map[name] = present;
	screens[present++] = screen;
	g_logger->info("Screen %s registered, id %d", name.c_str(), present - 1);
	return present - 1;
}

Screen *ScreenRegistry::getRegistered(int id)
{
	if (id >= present) throw BadScreenType();
	return screens[id];
}

Screen *ScreenRegistry::getRegistered(std::string name)
{
	if (map.find(name) == map.end()) throw BadScreenType();
	return screens[map[name]];
}

namespace Screens {
	int START;
	int WORLD;
};

void initScreen()
{
	static RegistryWrapper<ScreenRegistry, Screen> SCREENS =
		RegistryWrapper<ScreenRegistry, Screen>::
		getWrapper(&screenRegistry, "matrix");
	Screens::START = SCREENS.registered("start", new StartScreen());
	Screens::WORLD = SCREENS.registered("world", new WorldScreen());
}
