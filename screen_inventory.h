#pragma once
#include "cScreen.h"
class screen_inventory :
	public cScreen
{
public:
	virtual int Run(sf::RenderWindow& App, Player& player);
};

