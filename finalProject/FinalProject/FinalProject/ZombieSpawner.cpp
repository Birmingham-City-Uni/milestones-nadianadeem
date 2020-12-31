#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(SDL_Renderer* renderer, BulletManager* bulletManager, Player* player) : renderer(renderer), bulletManager(bulletManager), player(player) {};

void ZombieSpawner::init() {
	SDL_Surface* surface = IMG_Load("assets/SPRITES/misc/drone/drone-1.png");
	this->zombieTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

void ZombieSpawner::update() {
	if (SDL_GetTicks() - lastSpawnTime > WAVE_SPAWN_TIME) {
		currentWave++;
		for (int i = 0; i < currentWave; i++) {
			int location = rand() % (4-0) + 1;

			if (location == 0) {
				zombies.push_back(Zombie{ 32, 193 });
			}
			else if (location == 1) {
				zombies.push_back(Zombie{ 430,32 });
			}
			else if (location == 2) {
				zombies.push_back(Zombie{ 190, 896 });
			}
			else if (location == 3) {
				zombies.push_back(Zombie{ 400,450 });
			}
			else{
				zombies.push_back(Zombie{ 32, 800 });
			}
		}
		lastSpawnTime = SDL_GetTicks();
	}

	for (auto& z : zombies) {
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

		SDL_Rect playerRect = { player->position.x, player->position.y, 32, 32 };
		SDL_Rect zombieRect = { z.x, z.y, 32, 32 };

		if (SDL_IntersectRect(&playerRect, &zombieRect, &nullRect))
		{
			z.x = 0xCCCCCCCC;
			player->health = player->health - 50;
		}
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
