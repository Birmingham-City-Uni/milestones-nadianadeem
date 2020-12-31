#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "BulletManager.h"
#include "Player.h"

using namespace std;

struct Zombie {
	int x, y;
};

class ZombieSpawner {
	friend class TextRenderer;
public:
	ZombieSpawner(SDL_Renderer*, BulletManager*, Player*);
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
	Player* player;

	SDL_Rect playerRect;
	SDL_Rect bulletRect;
	SDL_Rect zombieRect;
	SDL_Rect nullRect;

	int zombiesShot = 0;

	const int WAVE_SPAWN_TIME = 10000;
	long int lastSpawnTime = 0;
	int currentWave = 0;
};