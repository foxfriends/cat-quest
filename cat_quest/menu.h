#ifndef __MENU_H__
#define __MENU_H__

#include "object.h"
#include "gamebase.h"
#include "room.h"

class Menu : public Object {
	int c_opt;
public:
	Menu(int, int, Sprite* = Gamebase::getSprite(4));

	void step();
	void draw();
};

#endif