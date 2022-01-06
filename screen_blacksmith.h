#pragma once
#include "cScreen.h"

class screen_blacksmith :
	public cScreen
{
public:
	virtual int Run(sf::RenderWindow& App, Player& player);
};

