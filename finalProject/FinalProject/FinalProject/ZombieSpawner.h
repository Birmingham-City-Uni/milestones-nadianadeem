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
public:
	ZombieSpawner(SDL_Renderer*, BulletManager*);
	void init();
	void update();
	void draw();
	void clean();

private:
	vector<Zombie> zombies;
	SDL_Renderer* renderer;
	SDL_Texture* zombieTexture;
	BulletManager* bulletManager;

	SDL_Rect bulletRect;
	SDL_Rect zombieRect;
	SDL_Rect nullRect;

	const int MAX_ZOMBIES = 2;
};