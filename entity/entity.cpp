#include "entity.hpp"
#include "../hook.hpp"
#include "../functions.hpp"

Entity::Entity()
	: x(0), y(0), z(0), facing(0)
{}

void Entity::teleport(double x_, double y_, double z_)
{
	x = x_, y = y_, z = z_;
}

void Entity::teleport(
	double x_, double y_, double z_, double facing_)
{
	teleport(x_, y_, z_);
	facing = facing_;
}

void Entity::teleportRelative(double x_, double y_, double z_)
{
	x += x_, y += y_, z += z_;
}

Player::Player()
	: LivingEntity(), jumps(0), newJump(false)
{
	for (int i = 0; i < 5; i++) directions[i] = false;
	mask = new bool *[16];
	for (int i = 0; i < 16; i++) {
		mask[i] = new bool[16];
		for (int j = 0; j < 16; j++) {
			mask[i][j] = true;
		}
	}
	maskW = maskH = 16;
}

void Player::pushGuiLayer(GuiLayer *layer)
{
	guis.push_back(layer);
}

void Player::popGuiLayer()
{
	delete guis.back();
	guis.pop_back();
}

void Player::updateScreen()
{
	for (auto it = guis.begin(); it < guis.end(); it++) {
		(*it)->update(true);
	}
}

void Player::updateEvent(SDL_Event *event)
{
	Hook *hook = 0;
	switch (event->type) {
		case SDL_KEYDOWN:
		{
			if (event->key.repeat == 0) {
				hook = new KeydownHook(event->key.keysym.sym);
				hookRegistry.pollHook(Hooks::KEYDOWN, hook);
			}
			break;
		}
		case SDL_KEYUP:
		{
			if (event->key.repeat == 0) {
				hook = new KeyupHook(event->key.keysym.sym);
				hookRegistry.pollHook(Hooks::KEYUP, hook);
			}
			break;
		}
	}
	if (hook) delete hook;
}

bool Player::collide(int i, int j)
{
	return mask[i][j];
}

static void hookKeydown(KeydownHook *hook)
{
	if (hook->getSym() == SDLK_w) g_player->setDirection(0, true);
	else if (hook->getSym() == SDLK_s) g_player->setDirection(1, true);
	else if (hook->getSym() == SDLK_a) g_player->setDirection(2, true);
	else if (hook->getSym() == SDLK_d) g_player->setDirection(3, true);
	else if (hook->getSym() == SDLK_SPACE) {
		g_player->setNewJump(true);
		g_player->setDirection(4, true);
	}
}

static void hookKeyup(KeyupHook *hook)
{
	if (hook->getSym() == SDLK_w) g_player->setDirection(0, false);
	else if (hook->getSym() == SDLK_s) g_player->setDirection(1, false);
	else if (hook->getSym() == SDLK_a) g_player->setDirection(2, false);
	else if (hook->getSym() == SDLK_d) g_player->setDirection(3, false);
	else if (hook->getSym() == SDLK_SPACE) g_player->setDirection(4, false);
}

void initEntity()
{
	hookRegistry.addListener(Hooks::KEYDOWN, (HookFunc) hookKeydown);
	hookRegistry.addListener(Hooks::KEYUP, (HookFunc) hookKeyup);
}
