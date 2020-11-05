#include "GameLoop.h"

#undef main

GameLoop* gameLoop;

int main(int argc, char* args[]) 
{
	gameLoop = new GameLoop();

	if (!gameLoop->init()) {
		return 1;
	}

	while (gameLoop->processInput()) {
		gameLoop->update();
		gameLoop->draw();
	}

	gameLoop->clean();

	delete gameLoop;
	return 0;
}