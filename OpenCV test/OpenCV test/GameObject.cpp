#include "StdAfx.h"
#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject(void)
{
	// Cleanup
	delete texture;
	delete sprite;
}

void GameObject::draw(RenderWindow& window)
{
	window.draw(*sprite);
}