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

struct Zombie {
	int x, y;
	int oldX, oldY;
	int tileX, tileY;
};

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
	vector<Zombie> zombies;
	SDL_Renderer* renderer;
	SDL_Texture* zombieTexture;
	BulletManager* bulletManager;
	Player* player;
	TiledMap* tiledMap;

	SDL_Rect playerRect;
	SDL_Rect bulletRect;
	SDL_Rect zombieRect;
	SDL_Rect nullRect;

	int zombiesShot = 0;

	const int WAVE_SPAWN_TIME = 10000;
	long int lastSpawnTime = 0;
	int currentWave = 0;
};