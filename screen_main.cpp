#include "screen_main.h"
#include "headers.h"
#include "general.h"

void heal(Character &player)
{
	long long int diff = player.getMaxHealth() - player.getHealth();
	if (diff <= player.getGold() && diff > 0)
	{
		player.setGold(player.getGold() - diff);
		player.setHealth(player.getMaxHealth());
	}
	else if (diff > 0)
	{
		player.addHealth(player.getGold());
		player.setGold(0);
	}
}

int screen_main::Run(sf::RenderWindow &App, Player& player)
{
	sf::Event Event;

	sf::Texture frameTexture;
	sf::Texture characterTexture;
	sf::Texture healthBarTexture;
	sf::Texture healthBarRedTexture;
	sf::Texture healthBackgroundTexture;
	sf::Texture goldTexture;

	sf::Font Font;

	sf::Sprite goldFrame;
	sf::Sprite goldIcon;
	sf::Sprite characterImage;
	sf::Sprite characterFrame;

	sf::Sprite playerHealthBar;
	sf::Sprite playerHealthBackground;

	sf::Sprite statsFrame;

	sf::Text stats;
	sf::Text playerHealth;
	sf::Text goldText;


	if (!frameTexture.loadFromFile("graphics/frame.png"))
	{
		std::cerr << "Error loading frame.png" << std::endl;
		return (GAME_ERROR);
	}

	if(!characterTexture.loadFromFile("graphics/character.png"))
	{
		std::cerr << "Error loading character.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!goldTexture.loadFromFile("graphics/gold.png"))
	{
		std::cerr << "Error loading gold.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!healthBarTexture.loadFromFile("graphics/health_bar.png"))
	{
		std::cerr << "Error loading health_bar.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!healthBarRedTexture.loadFromFile("graphics/health_bar_red.png"))
	{
		std::cerr << "Error loading health_bar_red.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!healthBackgroundTexture.loadFromFile("graphics/health_background.png"))
	{
		std::cerr << "Error loading health_background.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!Font.loadFromFile("data/arial.ttf"))
	{
		std::cerr << "Error loading data/arial.ttf" << std::endl;
		return (GAME_ERROR);
	}


	characterFrame.setTexture(frameTexture);
	characterFrame.setScale(0.55f, 1.0f);

	characterImage.setTexture(characterTexture);
	characterImage.setScale(1.0f, 1.0f);
	characterImage.setPosition(ScreenW*0.15f, ScreenH*0.4f);

	statsFrame.setTexture(frameTexture);
	statsFrame.setScale(0.25f, 0.30f);
	statsFrame.setPosition(ScreenW*0.55f, 0.0f);

	stats.setFont(Font);
	stats.setCharacterSize(20);
	stats.setFillColor(sf::Color::Black);
	stats.setPosition(ScreenW*0.58f, ScreenH*0.03f);

	initPlayerHealthBar(healthBarTexture, healthBackgroundTexture, playerHealthBar, playerHealthBackground, playerHealth, Font);
	initCurrencyStatus(goldTexture, goldIcon, frameTexture, goldFrame, goldText, Font);

	while (1)
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
					return EXIT_GAME; // TODO save screen
					break;
				case sf::Keyboard::G:
					player.addGold(20000);
					break;
				case sf::Keyboard::A:
					if(player.getHealth() > 0) return ADVENTURE_SCENE;
					break;
				case sf::Keyboard::S:
					return STATS_SCENE;
					break;
				case sf::Keyboard::H:
					heal(player);
					break;
				case sf::Keyboard::I:
					return INVENTORY_SCENE;
					break;
				case sf::Keyboard::M:
					return MERCHANT_SCENE;
					break;
				case sf::Keyboard::B:
					return BLACKSMITH_SCENE;
					break;
				case sf::Keyboard::L:
					player.lvlUp();
					break;
				case sf::Keyboard::P:
				{
					Item item1 = { WEAPON, 50, 0, 0, 0, 0 };
					Item item2 = { SHIELD, 0, 0, 200, 0, 0 };
					Item item3 = { ARMOR, 0, 0, 0, 200, 0 };
					Item item4 = { AMULET, 100, 100, 100, 100, 100 };
					player.addToBackpack(item1);
					player.addToBackpack(item2);
					player.addToBackpack(item3);
					player.addToBackpack(item4);
					break;
				}
				default:
					break;
				}
			}
		}

		//Updating data
		goldText.setString(std::to_string(player.getGold()));
		stats.setString("Strength: " + std::to_string(player.getStr()) + "\nMagic: " + std::to_string(player.getMag()) + "\nDefence: " + std::to_string(player.getDef()) + "\nVitality: " + std::to_string(player.getVit()) + "\nLuck: " + std::to_string(player.getLuck()) + "\nLevel: " + std::to_string(player.getLvl()));
		playerHealth.setString(std::to_string(player.getHealth()) + " / " + std::to_string(player.getMaxHealth()));
		
		playerHealthBar.setScale((float)player.getHealth() / (float)player.getMaxHealth(), 1.1f);
		if ((float)player.getHealth() / (float)player.getMaxHealth() < 0.25) playerHealthBar.setTexture(healthBarRedTexture);
		else playerHealthBar.setTexture(healthBarTexture);

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(characterFrame);
		App.draw(characterImage);
		App.draw(statsFrame);
		App.draw(stats);

		App.draw(playerHealthBackground);
		App.draw(playerHealthBar);

		App.draw(playerHealth);

		App.draw(goldFrame);
		App.draw(goldText);
		App.draw(goldIcon);

		App.display();
	}
	return (EXIT_GAME);
}