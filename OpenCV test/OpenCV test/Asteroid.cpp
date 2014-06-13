#include "StdAfx.h"
#include "Asteroid.h"


Asteroid::Asteroid()
{
	texture = new Texture();
	if(!texture->loadFromFile("asteroid.png"))
	{
		cout << "ERROR: Can't load file (asteroid.png)\n";
	}

	SYSTEMTIME time;
	GetSystemTime(&time);
	srand(time.wMilliseconds);
	int type = 1 + rand() % 4;
	IntRect* rect = 0;
	switch(type)
	{
	case 1:
		rect = new IntRect(Vector2i(0, 0), Vector2i(128, 128)); // Top left of spritesheet
		break;
	case 2:
		rect = new IntRect(Vector2i(128, 0), Vector2i(128, 128)); // Top right of spritesheet
		break;
	case 3:
		rect = new IntRect(Vector2i(0, 128), Vector2i(128, 128)); // Bottom left of spritesheet
		break;
	case 4:
		rect = new IntRect(Vector2i(128, 128), Vector2i(128, 128)); // Bottom right of spritesheet
		break;
	}
	sprite = new Sprite(*texture, *rect);
	sprite->setPosition((float)(rand() % 736), 0.0f); // Top random
}


Asteroid::~Asteroid(void)
{
}

bool Asteroid::update(Ship& ship)
{
	// Test collision
	if(intersects(ship.sprite, sprite))
	{
		return true;
	}
	
	sprite->move(0.0f, 4.0f);
	return false;
}
int Asteroid::getPosition()
{
	return (int)sprite->getPosition().y;
}
bool Asteroid::intersects(Sprite* a, Sprite* b)
{
	// Ship
	float x1 = a->getPosition().x;
	float y1 = a->getPosition().y;
	float w1 = 64.0f;
	float h1 = 128.0f;

	// Asteroid
	float x2 = b->getPosition().x;
	float y2 = b->getPosition().y;
	float w2 = 128.0f;
	float h2 = 128.0f;

	// Simple intersection check
	// 1) If not outside
	if(x2 > x1+w1 || x2+w2 < x1 || y2 > y1+h1 || y2+h2 < y1)
	{
		return false;
	}
	// 2) The it's intersecting
	return true;
}