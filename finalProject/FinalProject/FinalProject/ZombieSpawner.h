#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>
#include <iostream>

#include "BulletManager.h"
#include "Player.h"
#include "TiledMap.h"

using namespace std;

//Structure create to store attributes of the zombies created.
struct Zombie {
	int x, y;
	int oldX, oldY;
	int tileX, tileY;
	int nextMove;
};

//Methods created that are used by the ZombieSpawner script.
class ZombieSpawner {
	friend class TextRenderer;
public:
	ZombieSpawner(SDL_Renderer*, BulletManager*, Player*, TiledMap*);
	void init();
	void update();
	void draw();
	void clean();
	void createEdge(vector<int> adj[], int firstNode, int secondNode);
	bool BFS(vector<int> adj[], int s, int d, const int v, int previousVertex[]);
	void outputPath(vector<int> adj[], int s, int d, int v, int col);
	bool walkable(int i, int j, vector<vector<int>> M, int row, int col);
	void validatePath(vector<vector<int>> M, int col, int row, int V, vector<int> adj[], int tileX, int tileY);
	int getZombiesHit();

private:
//Vector to store all zombies on the screen.
	vector<Zombie> zombies;
//The renderer is stored to draw the zombies to the screen.
	SDL_Renderer* renderer;
//Store the texture of the zombie to be drawn.
	SDL_Texture* zombieTexture;
//Objects stored so their values can be used by this script.
	BulletManager* bulletManager;
	Player* player;
	TiledMap* tiledMap;

//Various SDL_Rects used to check collisions and locations of different objects.
	SDL_Rect playerRect;
	SDL_Rect bulletRect;
	SDL_Rect zombieRect;
	SDL_Rect nullRect;

//Used to keep track of the amount of zombies destroyed.
	int zombiesShot = 0;
//Stores the next move of the zombie.
	int nMove = 0;
//Stores the tile number that is itrated through to move the zombie to the correct point.
	int tileNo = 1;

//Time between waves is saved to trigger the waves to begin and zombies to spawn.
	const int WAVE_SPAWN_TIME = 10000;
//2 long integers stored to trigger the enemy wave spawning and the 1 second timer for the zombies to move closer to the enemy.
	long int lastSpawnTime = 0;
	long int checkTime = 0;
//This ineger is used to increase the current wave.
	int waveIncrease = 5;
//Current wave is used to specify how many zombies are to spawn each wave.
	int currentWave = 1;
};
