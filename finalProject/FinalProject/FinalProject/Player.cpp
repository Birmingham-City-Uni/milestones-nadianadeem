#include "Player.h"

Player::Player(SDL_Renderer* renderer, TiledMap* tiledMap)
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

	SDL_Rect healthBackground = { 5, 5, 100, 25 };
	SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(this->renderer, &healthBackground);
	float unitFactor = (float)100 / (float)100;
	int hpWidth = health * unitFactor;
	SDL_Rect healthBar = { 5, 5, hpWidth, 25 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &healthBar);

	if (health == 0) {
		position.x = 1000;
		position.y = 1000;
	}
}

void Player::update() {
	int oldX = position.x;
	int oldY = position.y;
}

void Player::processInput(bool* keyDown)
{
	int oldX = position.x;
	int oldY = position.y;
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

	SDL_Rect playerPos = { position.x, position.y,25,25 };
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 16; j++) {
			if (tiledMap->MAP_DATA[i][j] == 11 || tiledMap->MAP_DATA[i][j] == 5 || tiledMap->MAP_DATA[i][j] == 19 || tiledMap->MAP_DATA[i][j] == 9 || tiledMap->MAP_DATA[i][j] == 6 || tiledMap->MAP_DATA[i][j] == 10 || tiledMap->MAP_DATA[i][j] == 1 || tiledMap->MAP_DATA[i][j] == 14 || tiledMap->MAP_DATA[i][j] == 15) {
				SDL_Rect mapTile = { j * 32,i * 32,32,32 };
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					position.x = oldX;
					position.y = oldY;
				}
			}

			if (tiledMap->MAP_DATA[i][j] == 16) {
				SDL_Rect mapTile = { j * 32,i * 32,32,32 };
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					removeZombies = true;
					tiledMap->MAP_DATA[i][j] = 50;
				}
			}

			if (tiledMap->MAP_DATA[i][j] == 24) {
				SDL_Rect mapTile = { j * 32,i * 32,32,32 };
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					health = health + 50;
					tiledMap->MAP_DATA[i][j] = 50;
				}
			}

			else {
				SDL_Rect mapTile = { j * 32,i * 32,32,32 };
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					playerTileX = i;
					playerTileY = j;
				}
			}

		}
	}

	if (health > 100) {
		health = 100;
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