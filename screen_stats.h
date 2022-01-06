#pragma once
#include "cScreen.h"

class screen_stats :
	public cScreen
{
public:
	screen_stats(void) {};
	virtual int Run(sf::RenderWindow& App, Player& player);
};

