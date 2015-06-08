#ifndef __SPIKE_H__
#define __SPIKE_H__

#include "object.h"
#include "danger.h"

class Spike : public Object {
private:
	Danger* danger;
public:
	Spike(int, int, Sprite* = Gamebase::getSprite(3));
};

#endif