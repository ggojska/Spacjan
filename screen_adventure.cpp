#include "screen_adventure.h"
#include "headers.h"
#include "Player.h"
#include "general.h"

struct enemyStruct
{
	long long int level;
	bool boss;
};


enemyStruct printAdventureSelection(sf::RenderWindow &App, Player& player)
{
	bool inSelectionScreen = true;
	int choice = 1;
	char key = 0;

	sf::Texture frameTexture;
	sf::Sprite frame;
	sf::Font Font;

	std::vector<sf::Text> stages;

	Font.loadFromFile("data/arial.ttf");
	if (player.getLvl() <= 18)
	{
		for (int i = 1; i <= player.getLvl() + 1; i++)
		{
			sf::Text stage;
			stage.setFont(Font);
			stage.setCharacterSize(25);
			stage.setFillColor(sf::Color::Black);
			stage.setPosition(ScreenW*0.225f, i*ScreenH*0.04f);
			if(i == player.getLvl() + 1) stage.setString("BOSS: " + std::to_string(player.getLvl()));
			else stage.setString("LEVEL: " + std::to_string(i));
			stages.push_back(stage);
		}
	}
	else
	{
		for (int i = player.getLvl()-18; i <= player.getLvl() + 1; i++)
		{
			sf::Text stage;
			stage.setFont(Font);
			stage.setCharacterSize(25);
			stage.setFillColor(sf::Color::Black);
			stage.setPosition(ScreenW*0.225f, (i - (player.getLvl() - 19)) * ScreenH*0.04f);
			if (i == player.getLvl() + 1) stage.setString("BOSS: " + std::to_string(player.getLvl()));
			else stage.setString("LEVEL: " + std::to_string(i));
			stages.push_back(stage);
		}
	}

	frameTexture.loadFromFile("graphics/frame.png");

	frame.setTexture(frameTexture);
	frame.setScale(0.55f, 1.0f);

	sf::Event Event;

	while (inSelectionScreen)
	{
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return { -1, false };
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
				case sf::Keyboard::R:
					return {-1, true};
					break;
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					if(choice > 1) choice--;
					else if (20 > player.getLvl() + 1) choice = player.getLvl() + 1;
					else choice = 20;
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					if (choice < std::min((long long int)20, player.getLvl()+1)) choice++;
					else choice = 1;
					break;
				case sf::Keyboard::Enter:
				case sf::Keyboard::Space:
					if (player.getLvl() <= 18)
					{
						if (choice <= player.getLvl()) return { choice, false };
						else return { choice - 1, true };
					}
					else //player.getLvl() > 18
					{
						if (choice < player.getLvl() - (player.getLvl() - 20)) return {choice + (player.getLvl()-19), false };
						else return { choice + (player.getLvl() - 19) - 1, true };
					}
					break;
				default:
					break;
				}
			}
		}

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(frame);
		stages[choice-1].setFillColor(sf::Color::Red);
		for (auto stg : stages)
		{
			App.draw(stg);
		}
		App.display();
		stages[choice-1].setFillColor(sf::Color::Black);
	}
	return { -1, false };
}

void performAttack(Character& attacker, Character& defender)
{
	//std:: cout << "|" << attacker.getDamage() * defender.getDamageReduction(attacker) << " ";
	//std::cout << attacker.getDamage() << " ";
	defender.subHealth(attacker.getDamage() *(1 - defender.getDamageReduction(attacker)));

	if (typeid(attacker) == typeid(Player) && defender.getHealth() <= 0)
	{
		{
			if (attacker.getLvl() == defender.getLvl())
			{
				//attacker.addGold((attacker.getLuck() / 10)*defender.getGold());
				attacker.addExp(15);
			}
			else if (attacker.getLvl() < defender.getLvl())
			{
				//attacker.addGold((attacker.getLuck() / 10)*defender.getGold()*(1 + (defender.getLvl() - attacker.getLvl()) / 10));
				attacker.addExp(15* (1 + (defender.getLvl() - attacker.getLvl()) / 5));
			}
				else if (attacker.getLvl() > defender.getLvl())
			{
				//attacker.addGold(defender.getGold() / ((attacker.getLvl() - defender.getLvl())));
				attacker.addExp(15 / (attacker.getLvl() - defender.getLvl()));
			}
			attacker.addGold((attacker.getLuck() / 10) * defender.getGold());
		}
	}
	else if (typeid(defender) == typeid(Player) && defender.getHealth() <= 0)
	{
		defender.setGold(defender.getGold()*0.2);
		defender.setHealth(0);
	}
}

int screen_adventure::Run(sf::RenderWindow &App, Player& player)
{
	sf::Event Event;

	enemyStruct enemyData = { 0, false };
	enemyData = printAdventureSelection(App, player);
	Character enemy;
	enemy.setHealth(-1);

	if (enemyData.level == -1 && enemyData.boss == false)
	{
		return EXIT_GAME;
	}

	if (enemyData.level == -1 && enemyData.boss == true)
	{
		return MAIN_SCENE;
	}

	sf::Texture characterTexture;
	sf::Texture enemy1Texture;
	sf::Texture enemy2Texture;
	sf::Texture enemy3Texture;
	sf::Texture frameTexture;
	sf::Texture healthBarTexture;
	sf::Texture healthBarRedTexture;
	sf::Texture healthBackgroundTexture;
	sf::Texture backgroundTexture;
	sf::Texture goldTexture;

	sf::Font Font;

	std::vector<sf::Texture> texturesVector;

	sf::Sprite characterImage;
	sf::Sprite enemyImage;

	sf::Sprite background;
	sf::Sprite statsFrame;
	sf::Sprite enemyStatsFrame;
	sf::Sprite goldFrame;
	sf::Sprite goldIcon;
	sf::Sprite goldIcon2;
	sf::Sprite bossWindow;

	sf::Sprite playerHealthBar;
	sf::Sprite playerHealthBackground;
	
	sf::Sprite enemyHealthBar;
	sf::Sprite enemyHealthBackground;

	sf::Text playerHealth;	
	sf::Text enemyHealth;
	sf::Text stats;
	sf::Text enemyStats;
	sf::Text goldText;
	sf::Text bossText;

	if (!characterTexture.loadFromFile("graphics/character.png"))
	{
		std::cerr << "Error loading character.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!enemy1Texture.loadFromFile("graphics/enemy1.png"))
	{
		std::cerr << "Error loading enemy1.png" << std::endl;
		return (GAME_ERROR);
	}
	
	if (!enemy2Texture.loadFromFile("graphics/enemy2.png"))
	{
		std::cerr << "Error loading enemy2.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!enemy3Texture.loadFromFile("graphics/enemy3.png"))
	{
		std::cerr << "Error loading enemy3.png" << std::endl;
		return (GAME_ERROR);
	}

	if (!frameTexture.loadFromFile("graphics/frame.png"))
	{
		std::cerr << "Error loading frame.png" << std::endl;
		return (GAME_ERROR);
	}
	
	if (!backgroundTexture.loadFromFile("graphics/adventure_background.jpg"))
	{
		std::cerr << "Error loading adventure_background.jpg" << std::endl;
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

	//filling vector with enemy textures
	texturesVector.push_back(enemy1Texture);
	texturesVector.push_back(enemy2Texture);
	texturesVector.push_back(enemy3Texture);

	background.setTexture(backgroundTexture);
	background.setScale(1.0f, 1.0f);
	background.setPosition(0.0f, 0.0f);

	statsFrame.setTexture(frameTexture);
	statsFrame.setScale(0.25f, 0.30f);
	statsFrame.setPosition(ScreenW*0.55f, 0.0f);
	
	bossWindow.setTexture(frameTexture);
	bossWindow.setScale(0.4f, 0.4f);
	bossWindow.setPosition(ScreenW*0.3f, ScreenH*0.3f);

	enemyStatsFrame.setTexture(frameTexture);
	enemyStatsFrame.setScale(0.25f, 0.30f);
	enemyStatsFrame.setPosition(ScreenW*0.55f, ScreenH*0.45f);

	characterImage.setTexture(characterTexture);
	characterImage.setScale(0.5f, 0.5f);
	characterImage.setPosition(ScreenW*0.22f, ScreenH*0.65f);

	enemyImage.setScale(2.0f, 2.0f);
	enemyImage.setPosition(ScreenW*0.20f, ScreenH*0.3f);

	stats.setFont(Font);
	stats.setCharacterSize(20);
	stats.setFillColor(sf::Color::Black);
	stats.setPosition(ScreenW*0.58f, ScreenH*0.03f);
	
	enemyStats.setFont(Font);
	enemyStats.setCharacterSize(20);
	enemyStats.setFillColor(sf::Color::Black);
	enemyStats.setPosition(ScreenW*0.58f, ScreenH*0.48f);	

	bossText.setFont(Font);
	bossText.setCharacterSize(20);
	bossText.setFillColor(sf::Color::Black);
	bossText.setPosition(ScreenW*0.43f, ScreenH*0.35f);

	goldIcon2.setTexture(goldTexture);
	goldIcon2.setScale(0.6f, 0.6f);
	goldIcon2.setPosition(ScreenW*0.44f, ScreenH*0.43f);

	int enemyType = 1;

	initPlayerHealthBar(healthBarTexture, healthBackgroundTexture, playerHealthBar, playerHealthBackground, playerHealth, Font);
	initEnemyHealthBar(healthBarTexture, healthBackgroundTexture, enemyHealthBar, enemyHealthBackground, enemyHealth, Font);
	initCurrencyStatus(goldTexture, goldIcon, frameTexture, goldFrame, goldText, Font);

	if (enemyData.boss == true)
	{
		enemy = Character(enemyData.level, -1);
		enemyType = rand() % 3;
		enemyImage.setTexture(texturesVector[enemyType]);
		enemyImage.setScale(2.5f, 2.5f);
	}

	//clock_t time = clock();

	while (1)
	{
		//time = clock();
		if (enemy.getHealth() <= 0 && enemyData.boss == false)
		{
			enemyType = rand() % 3;
			enemy = Character(enemyData.level, enemyType);
			enemyImage.setTexture(texturesVector[enemyType]);
			enemyImage.setScale(2.0f, 2.0f);
		}

		if (player.getHealth() <= 0)
		{
			return MAIN_SCENE;
		}

		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return EXIT_GAME;
			}
			//Key pressed
			if (Event.type == sf::Event::KeyReleased)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
				case sf::Keyboard::R:
					return (MAIN_SCENE);
					break;
				case sf::Keyboard::Space:
					if (enemy.getHealth() > 0)
					{
						performAttack(player, enemy);
						if (enemy.getHealth() > 0) performAttack(enemy, player);
					}
					break;
				default:
					break;
				}
			}
		}
		if(enemy.getHealth() < 0) enemy.setHealth(0);

		/*
		if(time%200 == 0)
			performAttack(enemy, player);
		*/

		//Clearing screen
		App.clear();
		
		//Updating
		goldText.setString(std::to_string(player.getGold()));
		bossText.setString("Gratulations!\nYour reward:\n          " + std::to_string(enemy.getGold()));
		stats.setString("Strength: " + std::to_string(player.getStr()) + "\nMagic: " + std::to_string(player.getMag()) + "\nDefence: " + std::to_string(player.getDef()) + "\nVitality: " + std::to_string(player.getVit()) + "\nLuck: " + std::to_string(player.getLuck()) + "\nLevel: " + std::to_string(player.getLvl()));
		enemyStats.setString("ENEMY:\nStrength: " + std::to_string(enemy.getStr()) + "\nDefence: " + std::to_string(enemy.getDef()) + "\nVitality: " + std::to_string(enemy.getVit()));
		playerHealth.setString(std::to_string(player.getHealth()) + " / " + std::to_string(player.getMaxHealth()));
		enemyHealth.setString(std::to_string(enemy.getHealth()) + " / " + std::to_string(enemy.getMaxHealth()));
		playerHealthBar.setScale((float)player.getHealth() / (float)player.getMaxHealth(), 1.1f);
		enemyHealthBar.setScale((float)enemy.getHealth() / (float)enemy.getMaxHealth(), 1.1f);

		if ((float)player.getHealth() / (float)player.getMaxHealth() < 0.25) playerHealthBar.setTexture(healthBarRedTexture);
		else playerHealthBar.setTexture(healthBarTexture);
		
		if ((float)enemy.getHealth() / (float)enemy.getMaxHealth() < 0.25) enemyHealthBar.setTexture(healthBarRedTexture);
		else enemyHealthBar.setTexture(healthBarTexture);


		App.draw(background);

		App.draw(statsFrame);
		App.draw(stats);
		App.draw(enemyStatsFrame);
		App.draw(enemyStats);
		App.draw(goldFrame);
		App.draw(goldText);
		App.draw(goldIcon);
		//App.draw(characterImage);

		App.draw(enemyImage);

		App.draw(playerHealthBackground);
		App.draw(playerHealthBar);
		App.draw(enemyHealthBackground);
		App.draw(enemyHealthBar);

		App.draw(playerHealth);
		App.draw(enemyHealth);

		if (enemyData.boss == true && enemy.getHealth() <= 0)
		{
			App.draw(bossWindow);
			App.draw(bossText);
			App.draw(goldIcon2);
		}

		//Drawing
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return EXIT_GAME;
}