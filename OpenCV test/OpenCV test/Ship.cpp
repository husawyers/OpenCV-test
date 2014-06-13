#include "StdAfx.h"
#include "Ship.h"


Ship::Ship()
{
	texture = new Texture();
	if(!texture->loadFromFile("ship.png"))
	{
		cout << "ERROR: Can't load file (ship.png)\n";
		exit(-1);
	}

	sprite = new Sprite(*texture);
	sprite->setPosition(368, 472); // Bottom middle
}


Ship::~Ship(void)
{
}

void Ship::setPosition(int x)
{
	sprite->setPosition((float)x, sprite->getPosition().y);
}