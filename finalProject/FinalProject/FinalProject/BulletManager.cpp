#include "BulletManager.h"

//Takes the renderer, player and sound player as parameters. The renderer to display the bullets, the player to shoot the bullets for 
//the correct position and the soundplayer to play a shooting sound when bullets are fired.
BulletManager::BulletManager(SDL_Renderer* renderer, Player* player, SoundPlayer* sp) : renderer(renderer), player(player), sp(sp) {};

//Creates texture from the image "bullet.PNG" so it can be rendered to the window.
void BulletManager::init() 
{
	SDL_Surface* surface = IMG_Load("assets/bullet.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

//Checks if the player pressed the spacebar, if so a bullet is shot in the direct the player is facing the bullet will go as far as 70 pixels and then be deleted.
//Shots are delayed so the user cannot take advantage of the shooting mechanism.
//A sound effect of a bullet being shot is also played when the spacebar is pressed.
void BulletManager::processInput(bool* keyDown)
{
	if (keyDown[SDL_SCANCODE_SPACE]) 
	{
		if (SDL_GetTicks() - lastShot > SHOOT_DELAY) 
		{
			sp->PlayShot(1);
			bullets.push_back(Bullets{ player->getPosX() + 10, player->getPosY()+ 22 , 0, 0.0f });
			lastShot = SDL_GetTicks();
		}

		auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullets& b) {return b.distance > 70; });
		bullets.erase(remove, bullets.end());
	}
}

//Determines the direction the bullets should be shooting in by checking which direction the player is facing.
void BulletManager::update()
{
	if (player->facingRight) {
		for (auto& b : bullets) {
			b.x += BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingLeft) {
		for (auto& b : bullets) {
			b.x -= BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingUp) {
		for (auto& b : bullets) {
			b.rotation = 270;
			b.y -= BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}

	else if (player->facingDown) {
		for (auto& b : bullets) {
			b.rotation = 90;
			b.y += BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
	}
}

//Draws all the bullets that are needed to the screen in the correct direction and position.
void BulletManager::draw(){

	for (auto& b : bullets) {
		SDL_Rect dest = { b.x, b.y, 10, 10 };
		SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
	}
}

//Deletes the texture after the game has ended.
void BulletManager::clean() {
	SDL_DestroyTexture(this->bulletTexture);
}
