#include "screen_exit.h"
#include "game_save.h"

int screen_exit::Run(sf::RenderWindow& App, Player& player)
{
	sf::Event Event;
	bool Running = true;
	sf::Texture frameTexture;

	sf::Sprite characterFrame;
	sf::Sprite statsFrame;
	sf::Sprite goldFrame;

	sf::Font Font;
	int choice = 0;

	if (!frameTexture.loadFromFile("graphics/frame.png"))
	{
		std::cerr << "Error loading frame.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!Font.loadFromFile("data/arial.ttf"))
	{
		std::cerr << "Error loading data/arial.ttf" << std::endl;
		return (GAME_ERROR);
	}


	characterFrame.setTexture(frameTexture);
	characterFrame.setScale(0.8f, 0.8f);
	characterFrame.setPosition(0.1f*ScreenW, 0.1f*ScreenH);

	sf::Text question;
	question.setFont(Font);
	question.setCharacterSize(35);
	question.setFillColor(sf::Color::Black);
	question.setPosition(ScreenW*0.15f, ScreenH*0.3f);

	sf::Text yes;
	yes.setFont(Font);
	yes.setCharacterSize(30);
	yes.setFillColor(sf::Color::Black);
	yes.setPosition(ScreenW*0.48f, ScreenH*0.4f);

	sf::Text no;
	no.setFont(Font);
	no.setCharacterSize(30);
	no.setFillColor(sf::Color::Black);
	no.setPosition(ScreenW*0.48f, ScreenH*0.5f);

	sf::Text cancel;
	cancel.setFont(Font);
	cancel.setCharacterSize(30);
	cancel.setFillColor(sf::Color::Black);
	cancel.setPosition(ScreenW*0.45f, ScreenH*0.6f);

	sf::Text *menu[] = { &yes, &no , &cancel};

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (EXIT_GAME);
			}

			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
					return MAIN_SCENE;
					break;
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					choice--;
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					choice++;
					break;
				case sf::Keyboard::Enter:
					if (choice % 3 == 0)
					{
						saveGame(player);
						return EXIT_GAME;
					}
					else if (choice % 3 == 1) return EXIT_GAME;
					else return MAIN_SCENE;
					break;
				default:
					break;
				}
			}
		}

		//Updating data
		question.setString("Do you want to save game progress?");
		yes.setString("YES");
		no.setString("NO");
		cancel.setString("CANCEL");

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(characterFrame);
		App.draw(question);
		menu[abs(choice%3)]->setFillColor(sf::Color::Red);
		App.draw(*menu[0]);
		App.draw(*menu[1]);
		App.draw(*menu[2]);
		menu[abs(choice%3)]->setFillColor(sf::Color::Black);

		App.display();
	}
	return (EXIT_GAME);
}