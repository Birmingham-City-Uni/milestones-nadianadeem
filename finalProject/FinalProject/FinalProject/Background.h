#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Background {
public:
	Background(SDL_Renderer*);
	void init();
	void draw();
	void clean();

private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Rect position;
};
