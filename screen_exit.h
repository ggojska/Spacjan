#pragma once
#include "cScreen.h"
#include "Player.h"

class screen_exit :
	public cScreen
{
public:
	virtual int Run(sf::RenderWindow& App, Player& player);
};

