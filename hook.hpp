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

#ifndef __MATRIX_HOOK_HPP
#define __MATRIX_HOOK_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <exception>

#include "registry.hpp"
#include "settings.hpp"

class AmbigousHookError : std::exception {
	const char *what() const noexcept
	{ return "hook registry is ambigious"; };
};

class BadHookType : std::exception {
	const char *what() const noexcept
	{ return "bad hook type"; };
};

class Hook {
public:
	Hook() = default;
};

class CancelableHook : public Hook {
protected:
	bool canceled;

public:
	CancelableHook();
	bool getCanceled();
	void setCanceled();
};

class KeydownHook : public CancelableHook {
protected:
	int sym;

public:
	KeydownHook(int sym_);
	int getSym();
};

class KeyupHook : public CancelableHook {
protected:
	int sym;

public:
	KeyupHook(int sym_);
	int getSym();
};

class MousedownHook : public CancelableHook {
protected:
	int button, x, y;

public:
	MousedownHook(int button_, int x_, int y_);
	bool isClicked(int button_);
	int getButton();
	int getX();
	int getY();
};

typedef void (*HookFunc) (Hook *);

class HookRegistry {
	std::list<HookFunc> *hooks[Settings::MAX_HOOKS];
	std::unordered_map<std::string, int> map;
	int present;

public:
	HookRegistry();
	int registered(ResourceLocation name, Hook *hook);
	void addListener(int id, HookFunc func);
	void pollHook(int id, Hook *hook);
};

extern HookRegistry hookRegistry;

namespace Hooks {
	extern int KEYDOWN;
	extern int KEYUP;
	extern int MOUSEDOWN;
};

void initHook();

#endif
