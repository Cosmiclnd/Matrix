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
	exit(1);
}
