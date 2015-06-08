#ifndef __FISH_H__
#define __FISH_H__

#include "object.h"

class Fish : public Object {
	int yy, dy, timer;
public:
	Fish(int, int, Sprite* = Gamebase::getSprite(7));

	void step();
	void draw();
};

#endif