#include "BulletManager.h"

BulletManager::BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {};

void BulletManager::init() 
{
	SDL_Surface* surface = IMG_Load("assets/bullet.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

void BulletManager::processInput(bool* keyDown)
{
	if (keyDown[SDL_SCANCODE_SPACE]) 
	{
		if (SDL_GetTicks() - lastShot > SHOOT_DELAY) 
		{
			bullets.push_back(Bullets{ player->getPosX() + 10, player->getPosY()+ 22 , 0, 0.0f });
			lastShot = SDL_GetTicks();
		}

		auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullets& b) {return b.distance > 50; });
		bullets.erase(remove, bullets.end());
	}
}

void BulletManager::update()
{
	if (player->facingRight) {
		for (auto& b : bullets) {
			b.x += BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingLeft) {
		for (auto& b : bullets) {
			b.x -= BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingUp) {
		for (auto& b : bullets) {
			b.rotation = 270;
			b.y -= BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingDown) {
		for (auto& b : bullets) {
			b.rotation = 90;
			b.y += BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}
}

void BulletManager::draw(){
	SDL_Point center = { 1, 1};

	for (auto& b : bullets) {
		SDL_Rect dest = { b.x, b.y, 10, 10 };
		SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
	}
}

void BulletManager::clean() {
	SDL_DestroyTexture(this->bulletTexture);
}
