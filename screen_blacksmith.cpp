#include "screen_blacksmith.h"
#include "general.h"

void swap(Item& a, Item& b)
{
	std::swap(a.type, b.type);
	std::swap(a.strength, b.strength);
	std::swap(a.magic, b.magic);
	std::swap(a.defence, b.defence);
	std::swap(a.vitality, b.vitality);
	std::swap(a.luck, b.luck);
}

void updateBlacksmithItem(sf::Text& blacksmithText, Item blacksmithItem)
{
	if (blacksmithItem.type == 0) blacksmithText.setString("WEAPON\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else if (blacksmithItem.type == 1) blacksmithText.setString("SHIELD\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else if (blacksmithItem.type == 2) blacksmithText.setString("ARMOR\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else if (blacksmithItem.type == 3) blacksmithText.setString("HELMET\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else if (blacksmithItem.type == 4) blacksmithText.setString("BOOTS\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else if (blacksmithItem.type == 5) blacksmithText.setString("AMULET\nSTR:" + std::to_string(blacksmithItem.strength) + "\nMAG:" + std::to_string(blacksmithItem.magic) + "\nDEF:" + std::to_string(blacksmithItem.defence) + "\nVIT:" + std::to_string(blacksmithItem.vitality) + "\nLUC:" + std::to_string(blacksmithItem.luck));
	else blacksmithText.setString("");
}

void upgradeItem(Item& i, Player player)
{
	if (i.type == 0) i.strength += player.getLvl();
	else if (i.type == 1) i.defence += player.getLvl();
	else if (i.type == 2) i.defence += player.getLvl();
	else if (i.type == 3) i.vitality += player.getLvl();
	else if (i.type == 4) i.luck += player.getLvl();
	else if (i.type == 5)
	{
		i.strength += std::max((long long int)1 ,player.getLvl() / 4);
		i.magic += std::max((long long int)1, player.getLvl() / 4);
		i.defence += std::max((long long int)1, player.getLvl() / 4);
		i.vitality += std::max((long long int)1, player.getLvl() / 4);
		i.luck += std::max((long long int)1, player.getLvl() / 2);
	}
}

int screen_blacksmith::Run(sf::RenderWindow &App, Player& player)
{
	sf::Event Event;

	sf::Texture frameTexture;

	sf::Sprite backpack[BACKPACK_SIZE];
	sf::Sprite goldFrame;
	sf::Sprite blacksmith;
	sf::Sprite action;

	sf::Text backpackItems[BACKPACK_SIZE];
	sf::Text gold;
	sf::Text blacksmithText;
	sf::Text actionText;

	sf::RectangleShape frame;

	frame.setSize(sf::Vector2f(0.2f*ScreenW, 0.2f*ScreenH));
	frame.setOutlineColor(sf::Color::Red);
	frame.setOutlineThickness(5);
	frame.setFillColor(sf::Color(255, 255, 255, 0));
	frame.setPosition(0, 0);

	sf::Font Font;

	Item blacksmithItem = {(long long int) -1, 0, 0, 0, 0, 0 };

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

	goldFrame.setTexture(frameTexture);
	goldFrame.setScale(0.35f, 0.15f);
	goldFrame.setPosition(ScreenW*0.4f, ScreenH*0.0f);

	blacksmithText.setFont(Font);
	blacksmithText.setCharacterSize(17);
	blacksmithText.setFillColor(sf::Color::Black);
	blacksmithText.setPosition(ScreenW * 0.05f + ScreenW * 0.6f, ScreenH * 0.39f);

	blacksmith.setTexture(frameTexture);
	blacksmith.setScale(0.2f, 0.2f);
	blacksmith.setPosition(ScreenW * 0.6f, ScreenH * 0.4f);

	action.setTexture(frameTexture);
	action.setScale(0.2f, 0.1f);
	action.setPosition(ScreenW * 0.6f, ScreenH * 0.61f);

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
	gold.setPosition(ScreenW*0.03 + ScreenW * 0.4f, ScreenH*0.02 + ScreenH * 0.0f);
	
	actionText.setFont(Font);
	actionText.setCharacterSize(25);
	actionText.setFillColor(sf::Color::Black);
	actionText.setPosition(ScreenW*0.02 + ScreenW * 0.6f, ScreenH*0.02 + ScreenH * 0.6f);

	short selection = 0;
	long long int cost = pow(player.getLvl() * 10, 1.2);

	while (1)
	{
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
					if(blacksmithItem.type != -1)
						swap(blacksmithItem, player.backpack[player.findEmptyBackpackSlot()]);
					return 0;
					break;

				case sf::Keyboard::W:
					if (selection >= 2 && selection != -1) selection -= 2;
					else if (selection == -2) selection = -1;
					break;

				case sf::Keyboard::S:
					if (selection < 8 && selection != -1) selection += 2;
					else if (selection == -1) selection = -2;
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
					if (player.backpack[selection].type != -1 && blacksmithItem.type == -1 && selection > -1)
					{
						swap(player.backpack[selection], blacksmithItem);
					}
					else if (selection == -1 && blacksmithItem.type != -1)
					{
						swap(blacksmithItem, player.backpack[player.findEmptyBackpackSlot()]);
					}
					else if (selection == -2 && blacksmithItem.type != -1)
					{
						upgradeItem(blacksmithItem, player);
					}
					break;
				default:
					break;
				}
			}
		}

		if (selection > -1)
		{
			frame.setPosition(ScreenW * 0.2f*(selection % 2), ScreenH * 0.2f*(selection / 2));
			frame.setScale(1.0f, 1.0f);
		}
		else if (selection == -2)
		{
			frame.setPosition(ScreenW * 0.6f, ScreenH * 0.61f);
			frame.setScale(1.0f, 0.5f);
		}
		else
		{
			frame.setPosition(ScreenW * 0.6f, ScreenH * 0.4f);
			frame.setScale(1.0f, 1.0f);
		}

		//Updating data
		updateBlacksmithItem(blacksmithText, blacksmithItem);
		gold.setString("GOLD: " + std::to_string(player.getGold()));
		actionText.setString("UPGRADE");
		updateInterface(backpackItems, player);

		//Clearing screen
		App.clear();

		//Drawing
		for (int i = 0; i < BACKPACK_SIZE; i++)
		{
			App.draw(backpack[i]);
			App.draw(backpackItems[i]);
		}

		App.draw(frame);
		App.draw(blacksmith);
		App.draw(blacksmithText);
		App.draw(goldFrame);
		App.draw(gold);
		App.draw(action);
		App.draw(actionText);

		App.display();
	}
	return (-1);
}