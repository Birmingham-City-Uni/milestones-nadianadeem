#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Bullets.h"
#include "SoundPlayer.h"

using namespace std;

#define PI 3.14159265;

class BulletManager {
	friend class ZombieSpawner;
//Creates methods for the Bullet Manager to use.
public:
	BulletManager(SDL_Renderer* renderer, Player* player, SoundPlayer* sp);
	void init();
	void processInput(bool*);
	void update();
	void draw();
	void clean();

private:
//Stores the renderer and texture to be drawn to the screen.
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
//Stores all the bullets that are created by the user that need to be presented on the screen.
	vector<Bullets>bullets;
//Stores the player and sound player so their methods and variables can be manipulated by the bullet manager script.
	Player* player;
	SoundPlayer* sp;
	
//Center is the point where the bullet will be shot from.
	SDL_Point center = { 1, 1 };
//Integer that is used to stop the user spamming the spacebar and shooting lots of bullets.
	const int SHOOT_DELAY = 300;
//How quick the bullets will travel;
	const int BULLET_VELOCITY = 15;
//Stores when the last bullet was shot.
	unsigned int lastShot = 0;
};
