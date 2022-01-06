#include "screen_stats.h"
#include "headers.h"
#include "Player.h"
#include "general.h"

struct Prices
{
	long long int strPrice;
	long long int magPrice;
	long long int defPrice;
	long long int vitPrice;
	long long int luckPrice;
};

void updatePrices(Player& player, Prices& prices)
{
	Prices itemStats = { 0, 0, 0, 0, 0 };

	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		itemStats.strPrice += player.equipment[i].strength;
		itemStats.magPrice += player.equipment[i].magic;
		itemStats.defPrice += player.equipment[i].defence;
		itemStats.vitPrice += player.equipment[i].vitality;
		itemStats.luckPrice += player.equipment[i].luck;
	}

	prices.strPrice = pow(((player.getStr() - itemStats.strPrice)*1.5), 1.2);
	prices.magPrice = pow(((player.getMag() - itemStats.magPrice)*1.5), 1.2);
	prices.defPrice = pow(((player.getDef() - itemStats.defPrice)*1.5), 1.2);
	prices.vitPrice = pow(((player.getVit() - itemStats.vitPrice)*1.5), 1.2);
	prices.luckPrice = pow(((player.getLuck() - itemStats.luckPrice)*1.5), 1.2);
}

int screen_stats::Run(sf::RenderWindow &App, Player& player)
{
	Prices prices = { 0, 0, 0, 0, 0 };

	sf::Event Event;

	bool Running = true;

	sf::Texture frameTexture;
	sf::Texture characterTexture;
	sf::Texture goldTexture;

	sf::Font Font;

	sf::Sprite characterFrame;
	sf::Sprite statsFrame;
	sf::Sprite goldFrame;
	sf::Sprite goldIcon;

	sf::Text goldText;
	sf::Text stats;
	sf::Text statPrices;
	sf::Text unspentStatPoints;



	if (!frameTexture.loadFromFile("graphics/frame.png"))
	{
		std::cerr << "Error loading frame.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!characterTexture.loadFromFile("graphics/character.png"))
	{
		std::cerr << "Error loading character.png" << std::endl;
		return (GAME_ERROR);
	}
	
	if (!goldTexture.loadFromFile("graphics/gold.png"))
	{
		std::cerr << "Error loading gold.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!Font.loadFromFile("data/arial.ttf"))
	{
		std::cerr << "Error loading data/arial.ttf" << std::endl;
		return (GAME_ERROR);
	}

	characterFrame.setTexture(frameTexture);
	characterFrame.setScale(0.55f, 0.5f);

	statsFrame.setTexture(frameTexture);
	statsFrame.setScale(0.25f, 0.30f);
	statsFrame.setPosition(ScreenW*0.55f, 0.0f);

	stats.setFont(Font);
	stats.setCharacterSize(20);
	stats.setFillColor(sf::Color::Black);
	stats.setPosition(ScreenW*0.58f, ScreenH*0.03f);

	statPrices.setFont(Font);
	statPrices.setCharacterSize(25);
	statPrices.setFillColor(sf::Color::Black);
	statPrices.setPosition(ScreenW*0.05f, ScreenH*0.05f);
	
	unspentStatPoints.setFont(Font);
	unspentStatPoints.setCharacterSize(25);
	unspentStatPoints.setFillColor(sf::Color::Black);
	unspentStatPoints.setPosition(ScreenW*0.05f, ScreenH*0.35f);

	initCurrencyStatus(goldTexture, goldIcon, frameTexture, goldFrame, goldText, Font);

	while (Running)
	{
		updatePrices(player, prices);
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
					return 0; 
					break;
				case sf::Keyboard::Num1:
					if (player.getStatPts() > 0)
					{
						player.setStr(player.getStr() + 1);
						player.decStatPts();
					}
					else if (prices.strPrice <= player.getGold())
					{
						player.setGold(player.getGold() - prices.strPrice);
						player.setStr(player.getStr() + 1);
					}
					break;
				case sf::Keyboard::Num2:
					if (player.getStatPts() > 0)
					{
						player.setMag(player.getMag() + 1);
						player.decStatPts();
					}
					else if (prices.magPrice <= player.getGold())
					{
						player.setGold(player.getGold() - prices.magPrice);
						player.setMag(player.getMag() + 1);
					}
					break;
				case sf::Keyboard::Num3:
					if (player.getStatPts() > 0)
					{
						player.setDef(player.getDef() + 1);
						player.decStatPts();
					}
					else if (prices.defPrice <= player.getGold())
					{
						player.setGold(player.getGold() - prices.defPrice);
						player.setDef(player.getDef() + 1);
					}
					break;
				case sf::Keyboard::Num4:
					if (player.getStatPts() > 0)
					{
						player.setVit(player.getVit() + 1);
						player.decStatPts();
					}
					else if (prices.vitPrice <= player.getGold())
					{
						player.setGold(player.getGold() - prices.vitPrice);
						player.setVit(player.getVit() + 1);
					}
					break;
				case sf::Keyboard::Num5:
					if (player.getStatPts() > 0)
					{
						player.setLuck(player.getLuck() + 1);
						player.decStatPts();
					}
					else if (prices.luckPrice <= player.getGold())
					{
						player.setGold(player.getGold() - prices.luckPrice);
						player.setLuck(player.getLuck() + 1);
					}
					break;
				default:
					break;
				}
			}
		}

		//Updating data
		goldText.setString(std::to_string(player.getGold()));
		unspentStatPoints.setString("Unspent stat points: " + std::to_string(player.getStatPts()));
		stats.setString("Strength: " + std::to_string(player.getStr()) + "\nMagic: " + std::to_string(player.getMag()) + "\nDefence: " + std::to_string(player.getDef()) + "\nVitality: " + std::to_string(player.getVit()) + "\nLuck: " + std::to_string(player.getLuck()) + "\nLevel: " + std::to_string(player.getLvl()));
		statPrices.setString("STAT PRICES: \n1. Strength: " + std::to_string(prices.strPrice) + "\n2. Magic: " + std::to_string(prices.magPrice) + "\n3. Defence: " + std::to_string(prices.defPrice) + "\n4. Vitality: " + std::to_string(prices.vitPrice) + "\n5. Luck: " + std::to_string(prices.luckPrice) );

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(characterFrame);
		App.draw(statsFrame);
		App.draw(goldFrame);
		App.draw(stats);
		App.draw(statPrices);
		App.draw(unspentStatPoints);
		App.draw(goldText);
		App.draw(goldIcon);

		App.display();
	}
	return (-1);
}