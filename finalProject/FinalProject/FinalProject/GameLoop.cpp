#include "GameLoop.h"

GameLoop::GameLoop()
{
	//Creates variables to hold specific objects.
	window = nullptr;
	renderer = nullptr;
	bg = nullptr;
	buildings = nullptr;
	tm = nullptr;
	player = nullptr;

	//
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
}

bool GameLoop::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialise SDL: " << SDL_GetError();
		return false;
	}

	//Window is created with a width of 512px and a heigh of 960px.
	window = SDL_CreateWindow(
		"Space shooter",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		512, 960,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		std::cerr << "Could not create SDL window: " << SDL_GetError();
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer:" << SDL_GetError() << std::endl;
		return false;
	}

	//Initalises background and gives the renderer as a parameter so the background can be drawn.
	bg = new Background(this->renderer);
	bg->init();

	//Initalises buildings and gives the renderer as a parameter so the background can be drawn.
	buildings = new Buildings(this->renderer); 
	buildings->init();

	//Initalises the tilemap and gives the renderer as a parameter so the background can be drawn.
	tm = new TiledMap(this->renderer);
	tm->init();

	player = new Player(this->renderer);
	player->init();

	return true;
}

bool GameLoop::processInput() 
{
	SDL_Event e;
		
	//process any input for game classes here
	//player->processInput(e);

	return true;
}

void GameLoop::update() 
{

}

void GameLoop::draw() 
{
	//Draws everything to the window.
	SDL_RenderClear(renderer);
	bg->draw();
	buildings->draw();
	tm->draw();
	player->draw();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void GameLoop::clean() 
{

}

