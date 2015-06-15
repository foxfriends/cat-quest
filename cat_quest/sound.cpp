#include "sound.h"

int Sound::channelCount = 0;

Sound::Sound(char* url) {
	track = NULL;
	change(url);
}
Sound::~Sound() {
	free();
}
void Sound::free() {
	if(track != NULL) {
		Mix_FreeChunk(track);
		track = NULL;
	}
}
void Sound::change(char* url) {
	free();
	track = Mix_LoadWAV(url);
	if(track == NULL) {
		printf("Failed to load sound effect (%s)! SDL_mixer Error: %s\n", url, Mix_GetError());
		ok = false;
	} else {
		channel = channelCount++;
		ok = true;
	}
}
void Sound::play() {
	Mix_PlayChannel(channel, track, 0);
}
void Sound::stop() {
	Mix_HaltChannel(channel);
}

Music::Music(char* url) {
	track = NULL;
	change(url);
}
Music::~Music() {
	free();
}
void Music::free() {
	if(track != NULL) { 
		Mix_FreeMusic(track);
		track = NULL;
	}
}
void Music::play() {
	Mix_PlayMusic(track, -1);
}
void Music::change(char* url) {
	free();
	track = Mix_LoadMUS(url);
	if(track == NULL) {
		printf("Failed to load music (%s)! SDL_mixer Error: %s\n", url, Mix_GetError());
		ok = false;
	} else {
		ok = true;
	}
}
void Music::pause() {
	Mix_PauseMusic();
}
void Music::resume() {
	Mix_ResumeMusic();
}
void Music::stop() {
	Mix_HaltMusic();
}
bool Music::isPlaying() {
	return Mix_PlayingMusic() != 0;
}
bool Music::isPaused() {
	return Mix_PausedMusic() != 0;
}