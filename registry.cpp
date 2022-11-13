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

#include "registry.hpp"

ResourceLocation::ResourceLocation(std::string name_)
	: ResourceLocation("matrix", name_)
{}

ResourceLocation::ResourceLocation(std::string id_, std::string name_)
	: id(id_), name(name_)
{}

ResourceLocation::operator std::string()
{
	return id + ':' + name;
}

void Logger::print(const char *format, va_list va)
{
	char buf[1024];
	vsprintf(buf, format, va);
	std::cout << buf << std::endl;
}

void Logger::info(const char *format, ...)
{
	std::cout << "[Info] Matrix: ";
	va_list va;
	va_start(va, format);
	print(format, va);
	va_end(va);
}

void Logger::warn(const char *format, ...)
{
	std::cout << "[Warn] Matrix: ";
	va_list va;
	va_start(va, format);
	print(format, va);
	va_end(va);
}

void Logger::error(const char *format, ...)
{
	std::cout << "[Error] Matrix: ";
	va_list va;
	va_start(va, format);
	print(format, va);
	va_end(va);
}

void Logger::crash(const char *format, ...)
{
	std::cout << "Matrix Crashed:" << std::endl << "  ";
	va_list va;
	va_start(va, format);
	print(format, va);
	va_end(va);
	abort();
}
