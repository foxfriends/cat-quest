#ifndef __ENEMY_FLYING_BASIC_H__
#define __ENEMY_FLYING_BASIC_H__

#include "object.h"
#include "danger.h"
#include "wall.h"
#include "room.h"

class EnemyFlyingBasic : public Object {
private:
	Danger* danger;
	
public:
	EnemyFlyingBasic(int, int, Sprite* = Gamebase::getSprite(6));

	void step();
	void reverse();
	void die();
	Danger* getDanger();
};

#endif