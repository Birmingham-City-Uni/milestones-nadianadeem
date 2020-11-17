#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(SDL_Renderer* renderer, BulletManager* bulletManager) : renderer(renderer), bulletManager(bulletManager) {};

void ZombieSpawner::init() {
	SDL_Surface* surface = IMG_Load("assets/SPRITES/misc/drone/drone-1.png");
	this->zombieTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	for (int i = 0; i < MAX_ZOMBIES; i++) {
		zombies.push_back(Zombie{ 430, 32});
	}
}

void ZombieSpawner::update() {
	for (auto& z : zombies) {
		z.x -= 1;
		for (auto& b : bulletManager->bullets) {
			SDL_Rect bulletRect = { b.x, b.y, 10, 10 };
			SDL_Rect zombieRect = { z.x, z.y, 32, 32 };
			SDL_Rect nullRect;
			if (SDL_IntersectRect(&bulletRect, &zombieRect, &nullRect)) 
			{
				b.distance = 1000;
				z.x = 0xCCCCCCCC;
				zombiesShot += 1;
			}
		}
	}
	if (zombies.size() < MAX_ZOMBIES) {
		zombies.push_back(Zombie{ 440, 32 });
	}

	auto remove = std::remove_if(zombies.begin(), zombies.end(), [](const Zombie& z) {return z.x == 0xCCCCCCCC; });
	auto removeBullet = std::remove_if(bulletManager->bullets.begin(), bulletManager->bullets.end(), [](const Bullets& b) {return b.distance == 1000; });
	zombies.erase(remove, zombies.end());
	bulletManager->bullets.erase(removeBullet, bulletManager->bullets.end());
}

void ZombieSpawner::draw() {
	for (auto& z : zombies) {
		SDL_Rect dest = { z.x, z.y, 32, 32 };
		SDL_RenderCopy(renderer, zombieTexture, 0, &dest);
	}
}

void ZombieSpawner::clean() {
	SDL_DestroyTexture(this->zombieTexture);
}
int ZombieSpawner::getZombiesHit() {
	return zombiesShot;
}
