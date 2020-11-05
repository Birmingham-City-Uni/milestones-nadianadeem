#include "Background.h"

Background::Background(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = nullptr;
	this->position.x = 0, this->position.y = 0;
	this->position.w = 128, this->position.h = 128;
}

void Background::init() {
	SDL_Surface* surface = IMG_Load("assets/skyline-b.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	position.x = 0;
	position.y = 0;
	position.w = 512;
	position.h = 960;
}

void Background::draw() {
	SDL_RenderCopy(this->renderer, this->texture, 0, &this->position);
}
