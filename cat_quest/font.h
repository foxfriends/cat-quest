#ifndef __FONT_H__
#define __FONT_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "gameobject.h"

class Font : public GameObject {
	TTF_Font *font;
public:
	Font(char*, int);
	~Font();
	TTF_Font* getFont();

	void free();
	void change(char*, int);
};

#endif