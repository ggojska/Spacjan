#include "cScreen.h"
#include "Player.h"

class screen_adventure : public cScreen
{
private:
public:
	virtual int Run(sf::RenderWindow& App, Player& player);
};

