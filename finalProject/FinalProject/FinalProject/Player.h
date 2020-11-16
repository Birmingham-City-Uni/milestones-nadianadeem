#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Player {
public:
	Player(SDL_Renderer*);
	void init();
	void draw();
	void update();
	void processInput();
	void clean();
	float getPosX();
	float getPosY();

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect position;
};
