#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "object.h"
#include "gamebase.h"
#include "wall.h"
#include "goal.h"
#include "spike.h"
#include "fish.h"
#include "life.h"
#include "score.h"
#include "enemy_basic.h"
#include "enemy_flying_basic.h"
#include "draw.h"
#include "sdlx.h"
#include <vector>
#include <string>
#include <stdio.h>

class Player : public Object {
private:
	int jumpTimer, enemy_score_mult;
	static int score, lives, fish;
	bool dead;
public:
	Player(int, int, Sprite* = Gamebase::getSprite(Gamebase::sprite::player));

	static void resetLives();

	void step();

	void die();
	
	void catchView();

	void draw();
};

#include "room.h"

#endif