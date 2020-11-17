#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "BulletManager.h"

using namespace std;

struct Zombie {
	int x, y;
};

class ZombieSpawner {
	friend class TextRenderer;
public:
	ZombieSpawner(SDL_Renderer*, BulletManager*);
	void init();
	void update();
	void draw();
	void clean();
	int getZombiesHit();

private:
	vector<Zombie> zombies;
	SDL_Renderer* renderer;
	SDL_Texture* zombieTexture;
	BulletManager* bulletManager;

	SDL_Rect bulletRect;
	SDL_Rect zombieRect;
	SDL_Rect nullRect;

	const int MAX_ZOMBIES = 1;
	int zombiesShot = 0;
};