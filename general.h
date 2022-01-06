#pragma once

void initPlayerHealthBar(sf::Texture& healthBarTexture, sf::Texture& healthBackgroundTexture, sf::Sprite& healthBar, sf::Sprite& healthBackground, sf::Text& playerHealth, sf::Font& Font);

void initEnemyHealthBar(sf::Texture& healthBarTexture, sf::Texture& healthBackgroundTexture, sf::Sprite& healthBar, sf::Sprite& healthBackground, sf::Text& playerHealth, sf::Font& Font);

void initCurrencyStatus(sf::Texture& goldTexture, sf::Sprite& goldIcon, sf::Texture& frameTexture, sf::Sprite& goldFrame, sf::Text& goldText, sf::Font& Font);

void updateInterface(sf::Text backpackItems[], Player player);