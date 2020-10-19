#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

class GameLoop {
public:
	GameLoop();

	bool init();
	
	bool processInput();

	void update();

	void draw();

	void clean();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};