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

#include "item.hpp"
#include "../functions.hpp"

#include <SDL2/SDL2_rotozoom.h>

ItemRegistry itemRegistry;

Item::Item(Properties prop)
	: maxStack(prop.maxStack)
{}

int Item::getMaxStack()
{
	return maxStack;
}

SDL_Surface *Item::getSurface()
{
	return surface;
}

void Item::setSurface(SDL_Surface *surface_)
{
	surface = surface_;
}

ItemStack::ItemStack(int id_, int size_)
	: id(id_), size(size_)
{}

ItemRegistry::ItemRegistry()
	: present(0)
{
	for (int i = 0; i < Settings::MAX_ITEMS; i++) {
		items[i] = 0;
	}
}

int ItemRegistry::registered(ResourceLocation name_, Item *item)
{

	std::string name = name_;
	if (map.find(name) != map.end()) throw AmbigousItemError();
	map[name] = present;
	items[present++] = item;
	g_logger->info("Item %s registered, id %d", name.c_str(), present - 1);
	SDL_Surface *surface = loadTexture(name_.getName());
	if (!surface) {
		g_logger->warn("Loading debug texture instead");
		loadDebugTexture(name_, item);
		return present - 1;
	}
	item->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::ITEM_LENGTH_PIXEL / double(surface->w),
		Settings::ITEM_LENGTH_PIXEL / double(surface->h), 1));
	return present - 1;
}

Item *ItemRegistry::getRegistered(int id)
{
	if (id >= present) throw BadItemType();
	return items[id];
}

Item *ItemRegistry::getRegistered(std::string name)
{
	if (map.find(name) == map.end()) throw BadItemType();
	return items[map[name]];
}

void ItemRegistry::loadDebugTexture(ResourceLocation name_, Item *item)
{
	std::string name = name_;
	std::string filename = "assets/matrix/textures/item/debug.png";
	SDL_Surface *surface = tryLoadImage(filename);
	if (!surface) {
		g_logger->crash("Resource pack is damaged, failed to register %s",
			name.c_str());
	}
	item->setSurface(rotozoomSurfaceXY(surface, 0,
		Settings::ITEM_LENGTH_PIXEL / double(surface->w),
		Settings::ITEM_LENGTH_PIXEL / double(surface->h), 0));
}

SDL_Surface *ItemRegistry::loadTexture(std::string name)
{
	std::string filename = "assets/matrix/textures/item/" +
		name + ".png";
	SDL_Surface *surface = tryLoadImage(filename, false);
	if (!surface) {
		filename = "assets/matrix/textures/block/" +
			name + ".png";
		surface = tryLoadImage(filename);
	}
	return surface;
}

namespace Items {
	int STICK;
};

void initItem()
{
	static RegistryWrapper<ItemRegistry, Item *> ITEMS =
		RegistryWrapper<ItemRegistry, Item *>::getWrapper(
		&itemRegistry, "matrix");
	Items::STICK = ITEMS.registered("stick", new Item(Item::Properties()));
}
