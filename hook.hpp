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
};

void initHook();

#endif
