#include "tick.hpp"
#include "../functions.hpp"
#include "../settings.hpp"
#include "../maths.hpp"
#include "../gui/font.hpp"

#include <iostream>
#include <thread>

int g_ticks;

static bool safeTeleportRelative(Entity *entity, double x, double y, double z)
{
	static double ks[4] = { -1, -0.5, 0.495, 1 };
	int sx = Maths::sign(x), sy = Maths::sign(y), sz = Maths::sign(z);
	int ex = (entity->getX() + x + 1) * Settings::BLOCK_LENGTH_PIXEL;
	double ey = entity->getY();
	int ez = (entity->getZ() + z + 1) * Settings::BLOCK_LENGTH_PIXEL;
	int hmw = entity->getMaskW() / 2, hwh = entity->getMaskH() / 2;
	for (int i = -hmw; i < hmw - 1; i++) {
		for (int j = -hwh; j < hwh - 1; j++) {
			for (int ki = 0; ki < 4; ki++) {
				double k = ks[ki];
				BlockPos pos = {
					Maths::div(ex + i, Settings::BLOCK_LENGTH_PIXEL),
					int(round(ey + k)),
					Maths::div(ez + j, Settings::BLOCK_LENGTH_PIXEL)
				};
				int block = entity->getLevel()->getBlock(pos);
				if (block != -1 && blockRegistry.getRegistered(block)->
					collide(i + hmw, j + hwh)) {
					if ((k == -0.5 || k == 0.5) && (sx != 0 || sz != 0)) {
						return false;
					}
					if ((k == 1 || k == -1) && k == sy) {
						int cy = sy == 1 ? int(ey + y) : int(ey);
						if ((k == 1 && ey <= cy) ||
							(k == -1 && ey + y <= cy)) {
							entity->teleportRelative(0, cy - ey, 0);
							return false;
						}
					}
				}
			}
		}
	}
	entity->teleportRelative(x, y, z);
	return true;
}

static void playerJump(Player *player)
{
	int jumps = player->getJumps(), maxJumps = player->getMaxJumps();
	bool flag = false;
	if (jumps == 0) {
		if (player->getDy() == 0) {
			player->setDy(0.38);
			flag = true;
		}
	}
	else if (jumps < maxJumps && player->getNewJump()) {
		player->setDy(player->getDy() + 0.38);
		flag = true;
	}
	if (flag) {
		player->setNewJump(false);
		player->setJumps(jumps + 1);
	}
}

static void doTick()
{
	double speed = 0.1;
	if (g_player->getDy() != 0) {
		speed = 0.15;
	}
	if (g_player->getDirection(0)) safeTeleportRelative(g_player, 0, 0, speed);
	if (g_player->getDirection(1)) safeTeleportRelative(g_player, 0, 0, -speed);
	if (g_player->getDirection(2)) safeTeleportRelative(g_player, speed, 0, 0);
	if (g_player->getDirection(3)) safeTeleportRelative(g_player, -speed, 0, 0);
	if (g_player->getDirection(4)) {
		g_player->setMaxJumps(1);
		playerJump(g_player);
	}
	double oldDy = g_player->getDy(), dy = oldDy - g_player->getLevel()->getGravity();
	bool flag = true;
	for (int i = 0; i < 8; i++) {
		flag &= safeTeleportRelative(g_player, 0, dy / 8, 0);
		if (!flag) break;
	}
	if (flag) {
		g_player->setDy(dy);
	}
	else {
		g_player->setDy(0);
		g_player->setJumps(0);
	}
}

void funcTickUpdater()
{
	g_ticks = 0;
	std::chrono::steady_clock::time_point last =
		std::chrono::high_resolution_clock::now(), now;
	std::chrono::nanoseconds elapsed, deviation =
		std::chrono::nanoseconds::zero();
	while (!g_isQuit) {
		g_ticks++;
		doTick();
		now = std::chrono::high_resolution_clock::now();
		elapsed = now - last;
		elapsed = Settings::UPDATE_TICK_NANO - elapsed - deviation;
		std::this_thread::sleep_for(elapsed);
		last = std::chrono::high_resolution_clock::now();
		deviation = (deviation + last - now - elapsed) / 2;
	}
}
