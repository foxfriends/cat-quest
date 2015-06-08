#ifndef __DANGER_H__
#define __DANGER_H__

#include "object.h"

class Danger : public Object {
	friend class EnemyBasic;
public:
	Danger(int, int, Sprite* = Gamebase::getSprite(4));
	void move(int, int);
};

#endif