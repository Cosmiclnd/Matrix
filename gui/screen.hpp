#ifndef __GUI_SCREEN_HPP
#define __GUI_SCREEN_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <exception>
#include <chrono>

#include "../settings.hpp"
#include "../registry.hpp"
#include "../world/level.hpp"

class AmbigousScreenError : std::exception {
	const char *what() const noexcept
	{ return "screen registry is ambigious"; };
};

class BadScreenType : std::exception {
	const char *what() const noexcept
	{ return "bad screen type"; };
};

class Screen {
protected:
	int x, y, w, h;
	SDL_Surface *surface;
	SDL_Renderer *renderer;

public:
	Screen() = default;
	Screen(int x_, int y_, int w_, int h_);
	~Screen();
	virtual void update(bool show);
	Screen *make(void *player);
};

class StartScreen : public Screen {
public:
	StartScreen() = default;
	StartScreen(int x_, int y_, int w_, int h_);
	void update(bool show);
	StartScreen *make(void *player);
};

class WorldScreen : public Screen {
	int fps, showingFps;
	std::chrono::high_resolution_clock::time_point lastShowFps;

public:
	WorldScreen() = default;
	WorldScreen(int x_, int y_, int w_, int h_);
	void update(bool show);
	WorldScreen *make(void *player);

private:
	void showSubChunk(Chunk *chunk, SubChunk *subChunk, int x, int y, int z,
		double px, double py, double pz);
	void showPlayerScene();
	void showPos();
	void showFps();
};

class ScreenRegistry {
	Screen *screens[Settings::MAX_SCREENS];
	std::unordered_map<std::string, int> map;
	int present;

public:
	ScreenRegistry();
	int registered(ResourceLocation name, Screen *screen);
	Screen *getRegistered(int id);
	Screen *getRegistered(std::string name);
};

template <typename T>
T *makeNewScreen(int type, void *player);

namespace Screens {
	extern int START;
	extern int WORLD;
};

extern ScreenRegistry screenRegistry;

template <typename T>
T *makeNewScreen(int type, void *player)
{
	Screen *raw = screenRegistry.getRegistered(type);
	T *screen = (T *)raw;
	return screen->make(player);
}

void initScreen();

#endif
