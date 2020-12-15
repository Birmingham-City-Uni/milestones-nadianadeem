#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "TiledMap.h"

class Player {
public:
	Player(SDL_Renderer*, TiledMap*);
	void init();
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

private:

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect position;
	int angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};
