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

#include "hook.hpp"
#include "functions.hpp"

HookRegistry hookRegistry;

CancelableHook::CancelableHook()
	: Hook(), canceled(false)
{}

bool CancelableHook::getCanceled()
{
	return canceled;
}

void CancelableHook::setCanceled()
{
	canceled = true;
}

KeydownHook::KeydownHook(int sym_)
	: CancelableHook(), sym(sym_)
{}

int KeydownHook::getSym()
{
	return sym;
}

KeyupHook::KeyupHook(int sym_)
	: CancelableHook(), sym(sym_)
{}

int KeyupHook::getSym()
{
	return sym;
}

HookRegistry::HookRegistry()
	: present(0)
{
	for (int i = 0; i < Settings::MAX_HOOKS; i++) {
		hooks[i] = 0;
	}
}

int HookRegistry::registered(ResourceLocation name_, Hook *hook)
{
	std::string name = name_;
	if (map.find(name) != map.end()) throw AmbigousHookError();
	map[name] = present;
	hooks[present++] = new std::list<HookFunc>();
	g_logger->info("Hook %s registered, id %d", name.c_str(), present - 1);
	return present - 1;
}

void HookRegistry::addListener(int id, HookFunc func)
{
	if (id >= present) throw BadHookType();
	hooks[id]->push_back(func);
}

void HookRegistry::pollHook(int id, Hook *hook)
{
	if (id >= present) throw BadHookType();
	for (auto it = hooks[id]->begin(); it != hooks[id]->end(); it++) {
		((HookFunc) *it)(hook);
	}
}

namespace Hooks {
	int KEYDOWN;
	int KEYUP;
};

void initHook()
{
	static RegistryWrapper<HookRegistry, Hook *> HOOKS =
		RegistryWrapper<HookRegistry, Hook *>::
		getWrapper(&hookRegistry, "matrix");
	Hooks::KEYDOWN = HOOKS.registered("keydown", 0);
	Hooks::KEYUP = HOOKS.registered("keyup", 0);
}
