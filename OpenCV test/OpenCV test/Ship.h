#pragma once
#include "gameobject.h"

class Ship :
	public GameObject
{
	friend class Asteroid;

public:
	Ship();
	virtual ~Ship(void);

	void setPosition(int x);
};

