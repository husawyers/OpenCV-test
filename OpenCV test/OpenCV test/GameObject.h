#pragma once

#include "Headers.h"

class GameObject
{
protected:
	Texture *texture;
	Sprite *sprite;

public:
	GameObject();
	virtual ~GameObject(void);

	void draw(RenderWindow& window);
};

