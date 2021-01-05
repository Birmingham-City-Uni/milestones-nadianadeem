#include "Background.h"

//Sets the position, height and width of the background and takes the renderer as a parameter so the buildings can be shown.
Background::Background(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = nullptr;
	this->position.x = 0, this->position.y = 0;
	this->position.w = 128, this->position.h = 128;
}

//Creates a surface from the png file and then makes a texture using that surface and the renderer set in the parameter.
void Background::init() {
	SDL_Surface* surface = IMG_Load("assets/skyline-b.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	position.x = 0;
	position.y = 0;
	position.w = 512;
	position.h = 960;
}

//Draws the background to the window via the renderer.
void Background::draw() {
	SDL_RenderCopy(this->renderer, this->texture, 0, &this->position);
}

void Background::clean()
{
	SDL_DestroyTexture(this->texture);
}
