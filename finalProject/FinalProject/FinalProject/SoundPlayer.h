#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>

using namespace std;

enum Sounds {
	BACKINGTRACK = 0,
	GUNSHOT,
	TOTAL_SOUNDS,
};

class SoundPlayer {
public:
	SoundPlayer();
	virtual ~SoundPlayer();

	void PlaySound(int sound);
	void PlayShot(int sound);

private:
	Mix_Music* musicPlayer;
	vector<Mix_Chunk*> soundFiles;
};