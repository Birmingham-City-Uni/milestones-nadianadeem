#include "TiledMap.h"

extern TiledMap* tiledMap;

//Sets the renderer as the renderer given in the parameter. The mapTileSet is set as null as it is set later on.
TiledMap::TiledMap(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->mapTileSet = nullptr;
}

TiledMap::~TiledMap() {}

//Creates a texture from the image that is loaded as a surface.
void TiledMap::init() {
	SDL_Surface* s = IMG_Load("assets/tileset.png");
	this->mapTileSet = SDL_CreateTextureFromSurface(this->renderer, s);
	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 118;
	this->rect.h = 66;
	SDL_FreeSurface(s);
}

//Iterates through the MAP_DATA array and splits the tile map into 13px sections, each interger in the array correspondes to a specific tile section which is drawn to the screen.
void TiledMap::draw() {
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			SDL_Rect srcRect = { (MAP_DATA[i][j] % 9) * 13, ((MAP_DATA[i][j]) / 9) * 13, 13, 13};
			SDL_Rect destRict = { j * MAP_TITLE_SIZE_PX, i * MAP_TITLE_SIZE_PX, MAP_TITLE_SIZE_PX, MAP_TITLE_SIZE_PX };
			SDL_RenderCopy(this->renderer, this->mapTileSet, &srcRect, &destRict);
		}
	}
}