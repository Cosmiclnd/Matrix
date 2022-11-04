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

#ifndef __MATRIX_REGISTRY_HPP
#define __MATRIX_REGISTRY_HPP

#include <iostream>
#include <string>

class ResourceLocation {
	std::string id, name;

public:
	ResourceLocation(std::string name_);
	ResourceLocation(std::string id_, std::string name_);
	std::string getId() { return id; }
	std::string getName() { return name; }
	operator std::string();
};

template <typename T, typename U>
class RegistryWrapper {
	T *registry;
	std::string id;

public:
	int registered(std::string name, U *obj);
	static RegistryWrapper<T, U> getWrapper(T *registry, std::string id);
};

template <typename T, typename U>
int RegistryWrapper<T, U>::registered(std::string name, U *obj)
{
	return registry->registered(ResourceLocation(id, name), obj);
}

template <typename T, typename U>
RegistryWrapper<T, U> RegistryWrapper<T, U>::getWrapper(T *registry, std::string id)
{
	RegistryWrapper<T, U> wrapper;
	wrapper.registry = registry;
	wrapper.id = id;
	return wrapper;
}

class Logger {
	void print(const char *format, va_list va);

public:
	void info(const char *format, ...);
	void warn(const char *format, ...);
	void error(const char *format, ...);
	void crash(const char *format, ...);
};

#endif
