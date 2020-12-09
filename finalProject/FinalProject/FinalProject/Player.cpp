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
	//SDL_RenderCopy(this->renderer, this->texture, 0, &this->position);
	SDL_RenderCopyEx(this->renderer, this->texture, NULL, &this->position, angle, NULL, flip);
}

void Player::update() {

}

void Player::processInput(bool* keyDown)
{
	if (keyDown[SDL_SCANCODE_RIGHT]) {
		facingRight = true;
		facingLeft = false;
		facingDown = false;
		facingUp = false;
		this->position.x += 1;
		angle = 0;
		flip = SDL_FLIP_NONE;
	}
	else if (keyDown[SDL_SCANCODE_LEFT]) {
		facingRight = false;
		facingLeft = true;
		facingDown = false;
		facingUp = false;
		this->position.x -= 1;
		angle = 0;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyDown[SDL_SCANCODE_UP]) {
		facingRight = false;
		facingLeft = false;
		facingDown = false;
		facingUp = true;
		this->position.y -= 1;
		angle = 90;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyDown[SDL_SCANCODE_DOWN]) {
		facingRight = false;
		facingLeft = false;
		facingDown = true;
		facingUp = false;
		this->position.y += 1;
		angle = 90;
		flip = SDL_FLIP_NONE;
	}
}


void Player::clean() {

}

float Player::getPosX() {
	return position.x;
}

float Player::getPosY() {
	return position.y;
}