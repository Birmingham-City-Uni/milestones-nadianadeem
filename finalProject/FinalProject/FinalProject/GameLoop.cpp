#include "GameLoop.h"

GameLoop::GameLoop()
{
	window = nullptr;
	renderer = nullptr;
	bg = nullptr;
	buildings = nullptr;
	tm = nullptr;

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

	bg = new Background(this->renderer);
	bg->init();

	buildings = new Buildings(this->renderer); 
	buildings->init();

	tm = new TiledMap(this->renderer);
	tm->init();

	return true;
}

bool GameLoop::processInput() 
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
		}
		
		//process any input for game classes here
		//player->processInput(e);
	}

	return true;
}

void GameLoop::update() 
{

}

void GameLoop::draw() 
{
	SDL_RenderClear(renderer);
	bg->draw();
	buildings->draw();
	tm->draw();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void GameLoop::clean() 
{

}

