#include "Player.h"

Player::Player(SDL_Renderer* renderer) 
{
	this->renderer = renderer;
	this->texture = nullptr;
	this->position.x = 32, this->position.y = 32;
	this->position.w = 35, this->position.h = 35;
}

void Player::init() 
{
	SDL_Surface* surface = IMG_Load("assets/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_0.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

void Player::draw() 
{
	SDL_RenderCopy(this->renderer, this->texture, 0, &this->position);
}

void Player::update() {

}

void Player::clean() {

}

float Player::getPosX() {
	return position.x;
}

float Player::getPosY() {
	return position.y;
}