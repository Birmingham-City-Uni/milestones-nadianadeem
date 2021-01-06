#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

#include "TiledMap.h"

class Player {
public:
//Methods created for the player object.
	Player(SDL_Renderer*, TiledMap*);
	void init();
	void exit();
	void draw();
	void update();
	void processInput(bool*);
	void clean();
	float getPosX();
	float getPosY();
	
//These 4 booleans are used to track which way the player is facing.
	bool facingRight;
	bool facingLeft;
	bool facingUp;
	bool facingDown;

//Stores a tilemap to be used within methods.
	TiledMap* tiledMap;

//Creates 2 integers to keep track of the player's walkable position.
	int oldX = position.x;
	int oldY = position.y;

//Stores an SDL_Rect position to store the player's position.
	SDL_Rect position;

//Creates a float to store the players health.
	float health = 100;
//Stores the player's location as a tile number.
	int playerLoc;

//Stores the players X and Y in the context of the tile map.
	int playerTileX;
	int playerTileY;

//This boolean is used to for the unique game mechanic which is the bomb pick up.
	bool removeZombies = false;

//These SDL_Rects are used to check tile map collisions.
	SDL_Rect playerPos;
	SDL_Rect mapTile;

private:
//Stores the renderer and texture so the player can be drawn to the screen.
	SDL_Renderer* renderer;
	SDL_Texture* texture;
//Stores the angle at which the player is at.
	int angle = 0;
//Stores whether the image of the player has been flipped.
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	
};
