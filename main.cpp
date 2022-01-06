#include "headers.h"
#include "game_save.h"
#include "screens.h"


int main(int argc, char** argv)
{
	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	//Window creation
	sf::RenderWindow App(sf::VideoMode(ScreenW, ScreenH, 128), "Spacjan preAlpha 0.2");

	//Mouse cursor no more visible
	//App.setMouseCursorVisible(false);

	if (!canLoadGame())
	{
		Player initiate = Player(10, 10, 10, 10, 10, 1, 100);
		saveGame(initiate);
	}
	Player player = loadGame();
	//Screens preparations

	screen_main main;
	Screens.push_back(&main);
	screen_adventure adventure;
	Screens.push_back(&adventure);
	screen_stats stats;
	Screens.push_back(&stats);
	screen_inventory inventory;
	Screens.push_back(&inventory);
	screen_merchant merchant;
	Screens.push_back(&merchant);
	screen_blacksmith blacksmith;
	Screens.push_back(&blacksmith);

	screen_exit exit; 

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App, player);
		if (screen == -1)
		{
			screen = exit.Run(App, player);
		}
	}
	return EXIT_SUCCESS;
}