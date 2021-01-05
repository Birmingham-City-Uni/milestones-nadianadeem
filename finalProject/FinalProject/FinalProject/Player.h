#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

#include "TiledMap.h"

class Player {
public:
	Player(SDL_Renderer*, TiledMap*);
	void init();
	void exit();
	void draw();
	void update();
	void processInput(bool*);
	void clean();
	float getPosX();
	float getPosY();

	bool facingRight;
	bool facingLeft;
	bool facingUp;
	bool facingDown;

	TiledMap* tiledMap;

	int oldX = position.x;
	int oldY = position.y;

	SDL_Rect position;

	float health = 100;
	int playerLoc;

	int playerTileX;
	int playerTileY;

	bool removeZombies = false;

	SDL_Rect playerPos;
	SDL_Rect mapTile;

private:

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	
};
