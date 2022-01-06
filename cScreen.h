#pragma once
#include "Player.h"

class cScreen
{
	public:
		virtual int Run(sf::RenderWindow &App, Player& player) = 0;
};

