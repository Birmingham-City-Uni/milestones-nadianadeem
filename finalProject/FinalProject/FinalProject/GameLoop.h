#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "Background.h"
#include "Buildings.h"
#include "TiledMap.h"
#include "Player.h"
#include "BulletManager.h"
#include "ZombieSpawner.h"
#include "TextRenderer.h"
#include "SoundPlayer.h"

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
	stringstream zombieString;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Background* bg;
	Buildings* buildings;
	TiledMap* tm;
	Player* player;
	BulletManager* bm;
	ZombieSpawner* zs;
	TextRenderer* textRenderer;
	SoundPlayer* sp;


	bool keyDown[512];
};