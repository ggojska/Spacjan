#pragma once
#include "cScreen.h"
class screen_merchant :
	public cScreen
{
private:

public:
	virtual int Run(sf::RenderWindow &App, Player& player);
};

