#include "screen_merchant.h"
#include "general.h"

void generateItem(Item& i, Player player)
{
	i.type = rand() % EQUIPMENT_SIZE;
	if (i.type == WEAPON)
	{
		i.strength = rand() % (player.getLvl()+2) + 1;
		i.magic = rand() % (player.getLvl() + 2) + 1;
		i.defence = rand() % player.getLvl() / 3 + 1;
		i.vitality = rand() % player.getLvl() / 3 + 1;
		i.luck = rand() % player.getLvl() / 10 + 1;
	}
	else if (i.type == SHIELD)
	{
		i.strength = rand() % player.getLvl()/2 + 1;
		i.magic = rand() % (player.getLvl() + 1) + 1;
		i.defence = rand() % (player.getLvl() + 2) + 1;
		i.vitality = rand() % player.getLvl() + 1;
		i.luck = rand() % player.getLvl() / 10 + 1;
	}
	else if (i.type == ARMOR)
	{
		i.strength = rand() % player.getLvl() / 3 + 1;
		i.magic = rand() % player.getLvl() / 3 + 1;
		i.defence = rand() % (player.getLvl() + 2) + 1;
		i.vitality = rand() % (player.getLvl() + 2) + 1;
		i.luck = rand() % player.getLvl() / 3 + 1;
	}
	else if (i.type == HELMET)
	{
		i.strength = rand() % player.getLvl() / 3 + 1;
		i.magic = rand() % player.getLvl() / 3 + 1;
		i.defence = rand() % (player.getLvl() + 2) + 1;
		i.vitality = rand() % (player.getLvl() + 2) + 1;
		i.luck = rand() % player.getLvl() / 3 + 1;
	}
	else if (i.type == BOOTS)
	{
		i.strength = rand() % player.getLvl() / 3 + 1;
		i.magic = rand() % player.getLvl() / 3 + 1;
		i.defence = rand() % (player.getLvl() + 2) + 1;
		i.vitality = rand() % (player.getLvl() + 2) + 1;
		i.luck = rand() % player.getLvl() / 3 + 1;
	}
	else if (i.type == AMULET)
	{
		i.strength = rand() % (player.getLvl()+1) + 1;
		i.magic = rand() % (player.getLvl() + 1) + 1;
		i.defence = rand() % (player.getLvl() + 1) + 1;
		i.vitality = rand() % (player.getLvl() + 1) + 1;
		i.luck = rand() % (player.getLvl() + 2) +2;
	}

}

int screen_merchant::Run(sf::RenderWindow &App, Player& player)
{
	sf::Event Event;

	sf::Texture frameTexture;
	sf::Texture merchantTexture;
	sf::Texture goldTexture;

	sf::Sprite backpack[BACKPACK_SIZE];
	sf::Sprite merchant;
	sf::Sprite goldFrame;
	sf::Sprite goldIcon;
	sf::Sprite merchantBackground;

	sf::Text backpackItems[BACKPACK_SIZE];
	sf::Text merchantText;
	sf::Text gold;

	sf::RectangleShape frame;

	frame.setSize(sf::Vector2f(0.2f*ScreenW, 0.2f*ScreenH));
	frame.setOutlineColor(sf::Color::Red);
	frame.setOutlineThickness(5);
	frame.setFillColor(sf::Color(255, 255, 255, 0));
	frame.setPosition(0, 0);

	sf::Font Font;

	Item merchantItem = {(long long int) -1, 0, 0, 0, 0, 0};

	if (!frameTexture.loadFromFile("graphics/frame.png"))
	{
		std::cerr << "Error loading frame.png" << std::endl;
		return (GAME_ERROR);
	}
	
	if (!merchantTexture.loadFromFile("graphics/merchant.png"))
	{
		std::cerr << "Error loading merchant.png" << std::endl;
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
	
	merchantBackground.setTexture(merchantTexture);
	merchantBackground.setScale(1.0f, 1.0f);
	merchantBackground.setPosition(ScreenW*0.4f, ScreenH*0.0f);

	merchantText.setFont(Font);
	merchantText.setCharacterSize(17);
	merchantText.setFillColor(sf::Color::Black);
	merchantText.setPosition(ScreenW * 0.05f + ScreenW * 0.6f, ScreenH * 0.42f);

	merchant.setTexture(frameTexture);
	merchant.setScale(0.2f, 0.2f);
	merchant.setPosition(ScreenW * 0.6f, ScreenH * 0.4f);

	goldFrame.setTexture(frameTexture);
	goldFrame.setScale(0.35f, 0.15f);
	goldFrame.setPosition(ScreenW*0.4f, ScreenH*0.85f);

	goldIcon.setTexture(goldTexture);
	goldIcon.setScale(0.6f, 0.6f);
	goldIcon.setPosition(ScreenW*0.45f, ScreenH*0.90f);

	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		backpack[i].setTexture(frameTexture);
		backpack[i].setScale(0.2f, 0.2f);
		backpack[i].setPosition(ScreenW*0.2f*(i % 2), ScreenH * 0.2f*(i / 2));

		backpackItems[i].setFont(Font);
		backpackItems[i].setCharacterSize(17);
		backpackItems[i].setFillColor(sf::Color::Black);
		backpackItems[i].setPosition(ScreenW * 0.07f + ScreenW * 0.2f*(i % 2), ScreenH * 0.2f*(i / 2));
	}

	gold.setFont(Font);
	gold.setCharacterSize(25);
	gold.setFillColor(sf::Color::Black);
	gold.setPosition(ScreenW*0.03+ScreenW*0.5f, ScreenH*0.02 + ScreenH*0.89f);

	short selection = 0;
	long long int cost = pow(player.getLvl() * 10, 1.2);
	while (1)
	{
		if (merchantItem.type == -1)
		{
			generateItem(merchantItem, player);
		}
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

					case sf::Keyboard::W:
						if (selection >= 2 && selection != -1) selection -= 2;
						break;

					case sf::Keyboard::S:
						if (selection < 8 && selection != -1) selection += 2;
						break;

					case sf::Keyboard::A:
						if (selection % 2 != 0 && selection != -1) selection--;
						else if (selection == -1) selection = 5;
						break;

					case sf::Keyboard::D:
						if (selection % 2 != 1 && selection != -1) selection++;
						else  selection = -1;
						break;
					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						if(selection != -1)
						{
							if (player.backpack[selection].type != -1)
							{
								player.sellItem(selection);
							}
						}
						else
						{
							if (cost <= player.getGold())
							{
								if (player.addToBackpack(merchantItem))
								{
									player.setGold(player.getGold() - cost);
									merchantItem.type = (long long int)-1;
								}
							}
						}
						break;
					default:
						break;
					}
				}
			}

			if (selection != -1)
			{
				frame.setPosition(ScreenW * 0.2f*(selection % 2), ScreenH * 0.2f*(selection / 2));
				frame.setScale(1.0f, 1.0f);
			}
			else
			{
				frame.setPosition(ScreenW * 0.59f, ScreenH * 0.41f);
				frame.setScale(1.0f, 0.45f);
			}
		
		//Updating data
		gold.setString(std::to_string(player.getGold()));
		merchantText.setString("COST: \n" + std::to_string(cost));
		updateInterface(backpackItems, player);

		//Clearing screen
		App.clear();

		//Drawing
		for (int i = 0; i < BACKPACK_SIZE; i++)
		{
			App.draw(backpack[i]);
			App.draw(backpackItems[i]);
		}

		App.draw(merchantBackground);
		App.draw(frame);
		//App.draw(merchant);
		App.draw(merchantText);
		App.draw(goldFrame);
		App.draw(goldIcon);
		App.draw(gold);

		App.display();
	}
	return (-1);
}