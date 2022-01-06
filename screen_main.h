#include "cScreen.h"
#include "Player.h"

class screen_main : public cScreen
{
private:

public:
	virtual int Run(sf::RenderWindow &App, Player& player);
};
