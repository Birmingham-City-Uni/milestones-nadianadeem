#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Bullets.h"

using namespace std;

#define PI 3.14159265;

class BulletManager {
	friend class ZombieSpawner;
public:
	BulletManager(SDL_Renderer* renderer, Player* player);
	void init();
	void processInput(bool*);
	void update();
	void draw();
	void clean();

private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
	vector<Bullets>bullets;
	Player* player;

	const int SHOOT_DELAY = 300;
	const int BULLET_VELOCITY = 15;
	unsigned int lastShot = 0;
};