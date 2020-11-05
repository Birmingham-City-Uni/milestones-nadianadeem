#include "Buildings.h"

Buildings::Buildings(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = nullptr;
	this->position.x = 0, this->position.y = 0;
	this->position.w = 128, this->position.h = 128;
}

void Buildings::init() {
	SDL_Surface* surface = IMG_Load("assets/buildings-bg.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	position.x = 0;
	position.y = 450;
	position.w = 512;
	position.h = 512;
}

void Buildings::draw() {
	SDL_RenderCopy(this->renderer, this->texture, 0, &this->position);
}