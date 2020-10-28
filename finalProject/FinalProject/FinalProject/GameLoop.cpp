#include "GameLoop.h"

GameLoop::GameLoop()
{
	window = nullptr;
	renderer = nullptr;
	
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
		1280, 768,
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

	return true;
}

bool GameLoop::processInput() 
{
	return true;
}

void GameLoop::update() 
{

}

void GameLoop::draw() 
{

}

void GameLoop::clean() 
{

}

