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
	bm = nullptr;
	zs = nullptr;
	textRenderer = nullptr;
	sp = nullptr;

	//Stores user input.
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
}

bool GameLoop::init()
{
	//Trys to initialise SDL, if not an error message appears.
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

	//If a window cannot be created an error message is output to the console window.
	if (!window) {
		std::cerr << "Could not create SDL window: " << SDL_GetError();
		return false;
	}

	// Create renderer. If a renderer cannot be created an error message is displayed in the console window.
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

	//Initialises the sound player and plays the backing track to the game.
	sp = new SoundPlayer();
	sp->PlaySound(Sounds::BACKINGTRACK);


	//Initialises the player with the renderer as a parameter so the player can be drawn.
	//The tilemap is also a parameter to monitor the player's location on the map, as well as controlling collisions with the tilemap. 
	player = new Player(this->renderer, this->tm);
	player->init();

	player->tiledMap = tm;

	//Initialises the bullet manager with the renderer as a parameter so the bullets can be drawn to the window.
	//The player is another parameter so the bullets can be drawn and moved in the correct position and direction.
	//The sound player is a parameter so a shooting sound can be played when a bullet is shot.
	bm = new BulletManager(this->renderer, this->player, this->sp);
	bm->init();

	//Initialises the zombie spawner with the renderer as a parameter so the zombies can be drawn to the window.
	//The bullet manager is a parameter to track collisions between the bullets and the zombies.
	//The player is a parameter to track collsions between the player and the zombies.
	//The tilemap is a parameter to track the locations of zombies and is used in the pathfinding algorithm to get a path from the zombie to the player.
	zs = new ZombieSpawner(this->renderer, this->bm, this->player, this->tm);
	zs->init();

	//Textrenderer is initialised with the arial font at a size of 30.
	textRenderer = new TextRenderer("arial.ttf", 30);

	return true;
}

//Process input method is used to get the SDL_Event and use it to find which keys have been pressed and released.
bool GameLoop::processInput() 
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			//check against array size to prevent writing outside the bounds
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
		}
		else if (e.type == SDL_KEYUP) {
			//check against array size to prevent writing outside the bounds
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
		}

	}

	//Process input methods are carried out after the input has been processed.
	bm->processInput(keyDown);
	player->processInput(keyDown);

	return true;
}

//Objects update methods are ran here.
void GameLoop::update() 
{
	bm->update();
	zs->update();
	player->update();
}

//Objects draw methods are ran here as well as using the zombieString and the getZombiesHit method to renderer the players score.
void GameLoop::draw() 
{
	//Draws everything to the window.
	SDL_RenderClear(renderer);
	bg->draw();
	buildings->draw();
	bm->draw();
	tm->draw();
	player->draw();
	zs->draw();

	zombieString << "SCORE ";
	zombieString << zs->getZombiesHit();
	textRenderer->RenderString(this->renderer, zombieString.str(), 380, 0);

	zombieString.str(std::string());

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

//Frees memory after the game has been played by destroying any textures.
void GameLoop::clean() 
{
	bg->clean();
	buildings->clean();
	player->clean();
	textRenderer->clean();
	bm->clean();
	zs->clean();
	tm->clean();

	player->exit();

}

