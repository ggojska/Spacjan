#include "headers.h"
#include "Player.h"



void initPlayerHealthBar(sf::Texture& healthBarTexture, sf::Texture& healthBackgroundTexture, sf::Sprite& healthBar, sf::Sprite& healthBackground, sf::Text& playerHealth, sf::Font& Font)
{
	healthBar.setTexture(healthBarTexture);
	healthBar.setScale(1.0f, 1.1f);
	healthBar.setPosition(ScreenW*0.0f + 50, ScreenH*1.0f - 40);

	healthBackground.setTexture(healthBackgroundTexture);
	healthBackground.setScale(1.0f, 1.1f);
	healthBackground.setPosition(ScreenW*0.0f + 50, ScreenH*1.0f - 40);

	playerHealth.setFont(Font);
	playerHealth.setCharacterSize(25);
	playerHealth.setFillColor(sf::Color::Black);
	playerHealth.setPosition(ScreenW*0.0f + 150, ScreenH*1.0f - 43);
}

void initEnemyHealthBar(sf::Texture& healthBarTexture, sf::Texture& healthBackgroundTexture, sf::Sprite& healthBar, sf::Sprite& healthBackground, sf::Text& enemyHealth, sf::Font& Font)
{
	healthBar.setTexture(healthBarTexture);
	healthBar.setScale(1.0f, 1.1f);
	healthBar.setPosition(ScreenW*0.0f + 60, ScreenH*0.0f + 40);

	healthBackground.setTexture(healthBackgroundTexture);
	healthBackground.setScale(1.0f, 1.1f);
	healthBackground.setPosition(ScreenW*0.0f + 60, ScreenH*0.0f + 40);

	enemyHealth.setFont(Font);
	enemyHealth.setCharacterSize(25);
	enemyHealth.setFillColor(sf::Color::Black);
	enemyHealth.setPosition(ScreenW*0.0f + 150, ScreenH*0.0f + 38);
}

void initCurrencyStatus(sf::Texture& goldTexture, sf::Sprite& goldIcon, sf::Texture& frameTexture, sf::Sprite& goldFrame, sf::Text& goldText, sf::Font& Font)
{

	goldFrame.setTexture(frameTexture);
	goldFrame.setScale(0.35f, 0.15f);
	goldFrame.setPosition(ScreenW*0.55f, ScreenH*0.3f);

	goldIcon.setTexture(goldTexture);
	goldIcon.setScale(0.6f, 0.6f);
	goldIcon.setPosition(ScreenW*0.57f, ScreenH*0.35f);

	goldText.setFont(Font);
	goldText.setCharacterSize(25);
	goldText.setFillColor(sf::Color::Black);
	goldText.setPosition(ScreenW*0.64f, ScreenH*0.35f);
}

void updateInterface(sf::Text backpackItems[], Player player)
{
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