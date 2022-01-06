#include "screen_inventory.h"

void updateInterface(sf::Sprite equipped[], sf::Sprite backpack[], sf::Text equippedItems[], sf::Text backpackItems[], sf::Font Font, sf::Texture frameTexture, Player player)
{
	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		if (player.equipment[i].type == 0) equippedItems[i].setString("WEAPON\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else if (player.equipment[i].type == 1) equippedItems[i].setString("SHIELD\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else if (player.equipment[i].type == 2) equippedItems[i].setString("ARMOR\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else if (player.equipment[i].type == 3) equippedItems[i].setString("HELMET\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else if (player.equipment[i].type == 4) equippedItems[i].setString("BOOTS\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else if (player.equipment[i].type == 5) equippedItems[i].setString("AMULET\nSTR:" + std::to_string(player.equipment[i].strength) + "\nMAG:" + std::to_string(player.equipment[i].magic) + "\nDEF:" + std::to_string(player.equipment[i].defence) + "\nVIT:" + std::to_string(player.equipment[i].vitality) + "\nLUC:" + std::to_string(player.equipment[i].luck));
		else {
			if (i == 0) equippedItems[i].setString("WEAPON");
			else if (i == 1) equippedItems[i].setString("SHIELD");
			else if (i == 2) equippedItems[i].setString("ARMOR");
			else if (i == 3) equippedItems[i].setString("HELMET");
			else if (i == 4) equippedItems[i].setString("BOOTS");
			else if (i == 5) equippedItems[i].setString("AMULET");
		}
	}

	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		if (player.backpack[i].type == 0) backpackItems[i].setString("WEAPON\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else if (player.backpack[i].type == 1) backpackItems[i].setString("SHIELD\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else if (player.backpack[i].type == 2) backpackItems[i].setString("ARMOR\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else if (player.backpack[i].type == 3) backpackItems[i].setString("HELMET\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else if (player.backpack[i].type == 4) backpackItems[i].setString("BOOTS\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else if (player.backpack[i].type == 5) backpackItems[i].setString("AMULET\nSTR:" + std::to_string(player.backpack[i].strength) + "\nMAG:" + std::to_string(player.backpack[i].magic) + "\nDEF:" + std::to_string(player.backpack[i].defence) + "\nVIT:" + std::to_string(player.backpack[i].vitality) + "\nLUC:" + std::to_string(player.backpack[i].luck));
		else backpackItems[i].setString("");
	}
}

int screen_inventory::Run(sf::RenderWindow& App, Player& player)
{
	sf::Event Event;

	sf::Texture frameTexture;

	sf::Sprite equipped[EQUIPMENT_SIZE];
	sf::Sprite backpack[BACKPACK_SIZE];

	sf::Text equippedItems[EQUIPMENT_SIZE];
	sf::Text backpackItems[BACKPACK_SIZE];

	sf::RectangleShape frame;
	frame.setSize(sf::Vector2f(0.2f*ScreenW, 0.2f*ScreenH));
	frame.setOutlineColor(sf::Color::Red);
	frame.setOutlineThickness(5);
	frame.setFillColor(sf::Color(255, 255, 255, 0));
	frame.setPosition(0, 0);
	
	sf::RectangleShape bpframe;
	bpframe.setSize(sf::Vector2f(0.2f*ScreenW, 0.2f*ScreenH));
	bpframe.setOutlineColor(sf::Color::Red);
	bpframe.setOutlineThickness(5);
	bpframe.setFillColor(sf::Color(255, 255, 255, 0));
	bpframe.setPosition(0, 0);

	sf::Font Font;

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

	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		equipped[i].setTexture(frameTexture);
		equipped[i].setScale(0.2f, 0.2f);
		equipped[i].setPosition(ScreenW*0.2f*(i % 3), ScreenH*0.2f*(i / 3));

		equippedItems[i].setFont(Font);
		equippedItems[i].setCharacterSize(17);
		equippedItems[i].setFillColor(sf::Color::Black);
		equippedItems[i].setPosition(ScreenW * 0.07f + ScreenW * 0.2f*(i % 3), ScreenH*0.2f*(i / 3));
	}

	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		backpack[i].setTexture(frameTexture);
		backpack[i].setScale(0.2f, 0.2f);
		backpack[i].setPosition(ScreenW*0.2f*(i % 5), ScreenH*0.6f + ScreenH * 0.2f*(i / 5));

		backpackItems[i].setFont(Font);
		backpackItems[i].setCharacterSize(17);
		backpackItems[i].setFillColor(sf::Color::Black);
		backpackItems[i].setPosition(ScreenW * 0.07f + ScreenW * 0.2f*(i % 5), ScreenH*0.6f + ScreenH * 0.2f*(i / 5));
	}

	short selection = 0;
	short backpackSelection = 0;
	bool inEquipped = true;
	bool swap = false;
	while (1)
	{
		if (inEquipped)
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
						return 0;
						break;

					case sf::Keyboard::W:
						if (selection >= 3)
							selection -= 3;
						break;

					case sf::Keyboard::S:
						if (selection < 3)
							selection += 3;
						break;

					case sf::Keyboard::A:
						if (selection % 3 != 0)
							selection--;
						break;

					case sf::Keyboard::D:
						if (selection % 3 != 2)
							selection++;
						break;
					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						if (player.equipment[selection].type != -1)
						{
							swap = true;
							inEquipped = false;
							backpackSelection = 0;
						}
						else
						{
							inEquipped = false;
							backpackSelection = 0;
						}
						break;
					default:
						break;
					}
				}
			}
			frame.setPosition(ScreenW*0.2f*(selection % 3), ScreenH * 0.2f*(selection / 3));
		}
		else
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
						inEquipped = true;
						backpackSelection = 0;
						break;

					case sf::Keyboard::W:
						if (backpackSelection >= 5)
							backpackSelection -= 5;
						break;

					case sf::Keyboard::S:
						if (backpackSelection < 5)
							backpackSelection += 5;
						break;

					case sf::Keyboard::A:
						if (backpackSelection % 5 != 0)
							backpackSelection--;
						break;

					case sf::Keyboard::D:
						if (backpackSelection % 5 != 4)
							backpackSelection++;
						break;

					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						if (swap)
						{
							player.swapItem(selection, backpackSelection);
							swap = false;
							inEquipped = true;
							backpackSelection = 0;
						}
						else if (player.backpack[backpackSelection].type == selection)
						{
							player.equipItem(backpackSelection);
							inEquipped = true;
							backpackSelection = 0;
						}
						break;
					default:
						break;
					}
				}
			}
			bpframe.setPosition(ScreenW*0.2f*(backpackSelection % 5), ScreenH*0.6f + ScreenH * 0.2f*(backpackSelection / 5));
		}
		//Updating data
		updateInterface(equipped, backpack, equippedItems, backpackItems, Font, frameTexture, player);

		//Clearing screen
		App.clear();

		//Drawing
		for (int i = 0; i < EQUIPMENT_SIZE; i++)
		{
			App.draw(equipped[i]);
			App.draw(equippedItems[i]);
		}
		for (int i = 0; i < BACKPACK_SIZE; i++)
		{
			App.draw(backpack[i]);
			App.draw(backpackItems[i]);
		}

		App.draw(frame);
		if (!inEquipped) App.draw(bpframe);

		App.display();
	}
	return (-1);
}