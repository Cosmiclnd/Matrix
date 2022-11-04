#ifndef __ENTITY_ENTITY_HPP
#define __ENTITY_ENTITY_HPP

#include <vector>

#include "../gui/gui.hpp"
#include "../world/level.hpp"

class Entity {
protected:
	Level *current;
	double x, y, z, facing, dy;
	bool **mask;
	int maskW, maskH;

public:
	Entity();
	Level *getLevel() { return current; }
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double getDy() { return dy; }
	double getFacing() { return facing; }
	int getMaskW() { return maskW; }
	int getMaskH() { return maskH; }
	void setLevel(Level *new_) { current = new_; }
	void setDy(double dy_) { dy = dy_; }
	virtual void teleport(double x_, double y_, double z_);
	virtual void teleport(
		double x_, double y_, double z_, double facing_);
	virtual void teleportRelative(double x_, double y_, double z_);
	virtual bool collide(int i, int j) = 0;
};

class LivingEntity : public Entity {
protected:
	double health, maxHealth;

public:
	double getHealth() { return health; }
	double getMaxHealth() { return maxHealth; }
};

class Player : public LivingEntity {
	std::vector<GuiLayer *> guis;
	bool directions[5], newJump;
	int jumps, maxJumps;

public:
	Player();
	bool getDirection(int i) { return directions[i]; }
	bool getNewJump() { return newJump; }
	int getJumps() { return jumps; }
	int getMaxJumps() { return maxJumps; }
	void setDirection(int i, bool d) { directions[i] = d; }
	void setNewJump(bool newJump_) { newJump = newJump_; }
	void setJumps(int jumps_) { jumps = jumps_; }
	void setMaxJumps(int maxJumps_) { maxJumps = maxJumps_; }
	void pushGuiLayer(GuiLayer *layer);
	void popGuiLayer();
	void updateScreen();
	void updateEvent(SDL_Event *event);
	bool collide(int i, int j);
};

void initEntity();

#endif
