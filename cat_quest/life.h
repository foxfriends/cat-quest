#ifndef __LIFE_H__
#define __LIFE_H__

#include "object.h"

class Life : public Object {
	int yy, dy, timer;
public:
	Life(int, int, Sprite* = Gamebase::getSprite(9));

	void step();
	void draw();
};

#endif