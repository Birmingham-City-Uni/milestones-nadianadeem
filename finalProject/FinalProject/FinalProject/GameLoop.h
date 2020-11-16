#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Background.h"
#include "Buildings.h"
#include "TiledMap.h"
#include "Player.h"
#include "BulletManager.h"
#include "ZombieSpawner.h"

using namespace std;

class GameLoop {
public:
	GameLoop();

	bool init();
	
	bool processInput();

	void update();

	void draw();

	void clean();

	bool getKeyDown(int keyCode) {
		if (keyCode > 0 && keyCode < 512) {
			return this->keyDown[keyCode];
		}
		return false;
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Background* bg;
	Buildings* buildings;
	TiledMap* tm;
	Player* player;
	BulletManager* bm;
	ZombieSpawner* zs;

	bool keyDown[512];
};