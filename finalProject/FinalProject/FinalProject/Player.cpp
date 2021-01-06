#include "Player.h"

//Sets the renderer, width, height and position of the player.
Player::Player(SDL_Renderer* renderer, TiledMap* tiledMap)
{
	this->renderer = renderer;
	this->texture = nullptr;
	this->position.x = 32, this->position.y = 32;
	this->position.w = 35, this->position.h = 35;

}

//Creates the texture of the player from the image that is stored as a surface.
void Player::init() 
{
	SDL_Surface* surface = IMG_Load("assets/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_0.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

//Draws the player and health bar as well as checking collisions between the player and the tilemap.
void Player::draw() 
{
	SDL_RenderCopyEx(this->renderer, this->texture, NULL, &this->position, angle, NULL, flip);

//Creation of the health bar by drawing various rectangles and filling them in, in a certain colour.
	SDL_Rect healthBackground = { 5, 5, 100, 25 };
	SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(this->renderer, &healthBackground);
	float unitFactor = (float)100 / (float)100;
	int hpWidth = health * unitFactor;
	SDL_Rect healthBar = { 5, 5, hpWidth, 25 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &healthBar);

//If the player has no health left move the player off the screen.
	if (health == 0) {
		position.x = 1000;
		position.y = 1000;
	}
}

//Stores the position of the player in the variables oldX and oldY this is used to stop the player from moving
//when trying to move in an unwalkable tile.
void Player::update() {
	oldX = position.x;
	oldY = position.y;
}

void Player::processInput(bool* keyDown)
{
	oldX = position.x;
	oldY = position.y;
	//Moves, rotates and flips the player depending on the user's input.
	//Also keeps track of the direction the player is facing using 4 booleans.
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
	else if (keyDown[SDL_SCANCODE_ESCAPE]) {
		exit();
	}

//Stores the player's position and then checks every tile in the tile map to make sure that the player is in a walkable tile. If the player tried to move
//into an unwalkable tile the player will stop moving.
	playerPos = { position.x, position.y,25,25 };
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 16; j++) {
			mapTile = { j * 32,i * 32,32,32 };
			if (tiledMap->MAP_DATA[i][j] == 11 || tiledMap->MAP_DATA[i][j] == 5 || tiledMap->MAP_DATA[i][j] == 19 || tiledMap->MAP_DATA[i][j] == 9 || tiledMap->MAP_DATA[i][j] == 6 || tiledMap->MAP_DATA[i][j] == 10 || tiledMap->MAP_DATA[i][j] == 1 || tiledMap->MAP_DATA[i][j] == 14 || tiledMap->MAP_DATA[i][j] == 15) {
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					position.x = oldX;
					position.y = oldY;
				}
			}

			if (tiledMap->MAP_DATA[i][j] == 16) {
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					removeZombies = true;
					tiledMap->MAP_DATA[i][j] = 50;
				}
			}

			if (tiledMap->MAP_DATA[i][j] == 24) {
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					health = health + 50;
					tiledMap->MAP_DATA[i][j] = 50;
				}
			}

			else {
				if (SDL_HasIntersection(&playerPos, &mapTile)) {
					playerTileX = i;
					playerTileY = j;
				}
			}

		}
	}

	//Limits the health of the player to 100.
	if (health > 100) {
		health = 100;
	}
}

//Destroys the texture of the player to free memory.
void Player::clean() {
	SDL_DestroyTexture(this->texture);
}
//Returns the X position of the player.
float Player::getPosX() {
	return position.x;
}

//Return the Y position of the player.
float Player::getPosY() {
	return position.y;
}

//Quits SDL when executed.
void Player::exit()
{
	SDL_Quit();
}
