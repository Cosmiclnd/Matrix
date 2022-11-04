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
	static RegistryWrapper<HookRegistry, Hook> HOOKS =
		RegistryWrapper<HookRegistry, Hook>::
		getWrapper(&hookRegistry, "matrix");
	Hooks::KEYDOWN = HOOKS.registered("keydown", 0);
	Hooks::KEYUP = HOOKS.registered("keyup", 0);
}
