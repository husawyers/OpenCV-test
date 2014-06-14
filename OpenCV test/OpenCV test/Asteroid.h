#pragma once
#include "gameobject.h"
#include "Ship.h"
class Asteroid :
	public GameObject
{
public:
	Asteroid();
	virtual ~Asteroid(void);

	bool update(Ship& ship, int speed);
	int getPosition();
	bool intersects(Sprite* a, Sprite* b);
};

