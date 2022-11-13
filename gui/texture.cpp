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

#include "texture.hpp"
#include "../functions.hpp"

TextureRegistry textureRegistry;

int TextureRegistry::registered(ResourceLocation name_, std::string path)
{
	std::string name = name_;
	if (map.find(name) != map.end()) throw AmbigousTextureError();
	std::string filepath = "assets/" + name_.getId() + "/textures/" + path;
	SDL_Surface *surface = forceLoadImage(filepath);
	map[name] = surface;
	g_logger->info("Texture %s loaded", name.c_str());
	return 0;
}

SDL_Surface *TextureRegistry::getRegistered(std::string name)
{
	if (map.find(name) == map.end()) throw BadTextureType();
	return map[name];
}

void initTexture()
{
	static RegistryWrapper<TextureRegistry, std::string> TEXTURES =
		RegistryWrapper<TextureRegistry, std::string>::
		getWrapper(&textureRegistry, "matrix");
	TEXTURES.registered("over_block", "gui/world/over_block.png");
	TEXTURES.registered("pickaxe", "gui/world/pickaxe.png");
	TEXTURES.registered("sword", "gui/world/sword.png");
	TEXTURES.registered("selected", "gui/world/selected.png");
	TEXTURES.registered("widgets", "gui/world/widgets.png");
}
