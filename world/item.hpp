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

#ifndef __WORLD_ITEM_HPP
#define __WORLD_ITEM_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <exception>

#include "../settings.hpp"
#include "../registry.hpp"

class AmbigousItemError : std::exception {
	const char *what() const noexcept
	{ return "item registry is ambigious"; };
};

class BadItemType : std::exception {
	const char *what() const noexcept
	{ return "bad item type"; };
};

class Item {
	int maxStack;
	SDL_Surface *surface;

public:
	class Properties {
		int maxStack;
	
	public:
		Properties() : maxStack(64) {}
		Properties setMaxStack(int x) { maxStack = x; return *this; }

		friend class Item;
	};

	Item(Properties prop);
	int getMaxStack();
	SDL_Surface *getSurface();
	void setSurface(SDL_Surface *surface_);
};

class ItemStack {
	int id, size;

public:
	ItemStack(int id_, int size_);
};

class ItemRegistry {
	Item *items[Settings::MAX_ITEMS];
	std::unordered_map<std::string, int> map;
	int present;

public:
	ItemRegistry();
	int registered(ResourceLocation name, Item *item);
	Item *getRegistered(int id);
	Item *getRegistered(std::string name);
	void loadDebugTexture(ResourceLocation name, Item *item);
};

namespace Items {
	extern int STICK;
};

void initItem();

extern ItemRegistry itemRegistry;

#endif
