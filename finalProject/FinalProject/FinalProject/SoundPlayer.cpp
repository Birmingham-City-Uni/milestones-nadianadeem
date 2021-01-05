#include "SoundPlayer.h"
#include "stdafx.h"

SoundPlayer::SoundPlayer()
{
	if (Mix_OpenAudio(22050, 0x8010, 2, 4096) == -1) {
		printf("Audio Mixer could not be created! SDL_Error %s\n", SDL_GetError());
	}
	for (int i = 0; i < TOTAL_SOUNDS; i++) {
		stringstream name;
		name << i;
		name << ".wav";
		Mix_Chunk* sound = Mix_LoadWAV_RW(SDL_RWFromFile(name.str().c_str(), "rb"), 1);
		soundFiles.push_back(sound);
	}
}

SoundPlayer::~SoundPlayer()
{
	for (auto& sound : soundFiles) {
		Mix_FreeChunk(sound);
	}
	Mix_FreeMusic(musicPlayer);
}

void SoundPlayer::PlaySound(int sound)
{
	//Mix_PlayChannel(-1, soundFiles[sound], 0);
	Mix_PlayChannelTimed(2, soundFiles[sound], 100, 0);

}

void SoundPlayer::PlayShot(int sound)
{
	Mix_PlayChannelTimed(1, soundFiles[sound], 0, 0);
}
