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

#ifndef __GUI_TEXTURE_HPP
#define __GUI_TEXTURE_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

#include "../registry.hpp"

class AmbigousTextureError : std::exception {
	const char *what() const noexcept
	{ return "texture registry is ambigious"; };
};

class BadTextureType : std::exception {
	const char *what() const noexcept
	{ return "bad texture type"; };
};

class TextureRegistry {
	std::unordered_map<std::string, SDL_Surface *> map;

public:
	int registered(ResourceLocation name, std::string path);
	SDL_Surface *getRegistered(std::string name);
};

extern TextureRegistry textureRegistry;

void initTexture();

#endif
