#ifndef __SOUND_H__
#define __SOUND_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "gameobject.h"

class Sound : public GameObject {
	Mix_Chunk* track;
	int channel;
	static int channelCount;
public:
	Sound(char*);
	~Sound();
	void change(char*);
	void free();

	void play();
	void stop();
};

class Music : public GameObject {
	Mix_Music* track;
public:
	Music(char*);
	~Music();
	void change(char*);
	void free();

	void play();
	static void pause();
	static void resume();
	static void stop();
	static bool isPlaying();
	static bool isPaused();
};

#endif