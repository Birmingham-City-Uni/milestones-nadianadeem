#include "TiledMap.h"

extern TiledMap* tiledMap;

TiledMap::TiledMap(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->mapTileSet = nullptr;
}

TiledMap::~TiledMap() {}

void TiledMap::init() {
	SDL_Surface* s = IMG_Load("assets/tileset.png");
	this->mapTileSet = SDL_CreateTextureFromSurface(this->renderer, s);
	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 514;
	this->rect.h = 960;
	SDL_FreeSurface(s);
}

void TiledMap::draw() {
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			SDL_Rect srcRect = { (MAP_DATA[i][j] % 6) * 12, ((MAP_DATA[i][j]) / 5) * 12, 12, 12};
			SDL_Rect destRict = { j * MAP_TITLE_SIZE_PX, i * MAP_TITLE_SIZE_PX, MAP_TITLE_SIZE_PX, MAP_TITLE_SIZE_PX };
			SDL_RenderCopy(this->renderer, this->mapTileSet, &srcRect, &destRict);
		}
	}
	//SDL_RenderCopy(this->renderer, this->mapTileSet, 0, &this->rect);
}