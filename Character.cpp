#include "Character.h"
#include "headers.h"

long long int generateNumber(long long int min, long long int max)
{
	return rand() % (max - min) + min;
}

Character::Character(long long int str, long long int def, long long int vit, long long int gold, long long int lvl)
{
	this->strength = str;
	this->defence = def;
	this->vitality = vit;
	this->gold = gold;
	this->setHealth();
	this->health = this->maxHealth;
	this->damage = this->strength;
	this->level = lvl;
}

Character::Character(long long int lvl, short type)
{
	if (type == -1)
	{
		this->strength = generateNumber(lvl * 11, lvl * 14);
		this->defence = generateNumber(lvl * 11, lvl * 14);
		this->vitality = generateNumber(lvl * 11, lvl * 14);
		this->gold = generateNumber(lvl * 80, lvl * 100);
		this->setHealth();
		this->health = this->maxHealth;
		this->damage = this->strength;
		this->level = lvl;
	}
	else if (type == 0)
	{
		this->strength = generateNumber(lvl * 6, lvl * 8);
		this->defence = generateNumber(lvl * 10, lvl * 13);
		this->vitality = generateNumber(lvl * 6, lvl * 7);
		this->gold = generateNumber(lvl * 8, lvl * 9);
		this->setHealth();
		this->health = this->maxHealth;
		this->damage = this->strength;
		this->level = lvl;
	}
	else if (type == 1)
	{
		this->strength = generateNumber(lvl * 10, lvl * 13);
		this->defence = generateNumber(lvl * 6, lvl * 9);
		this->vitality = generateNumber(lvl * 3, lvl * 5);
		this->gold = generateNumber(lvl * 6, lvl * 8);
		this->setHealth();
		this->health = this->maxHealth;
		this->damage = this->strength;
		this->level = lvl;
	}
	else if (type == 2)
	{
		this->strength = generateNumber(lvl * 12, lvl * 14);
		this->defence = generateNumber(lvl * 2, lvl * 4);
		this->vitality = generateNumber(lvl * 3, lvl * 4);
		this->gold = generateNumber(lvl * 1, lvl * 17);
		this->setHealth();
		this->health = this->maxHealth;
		this->damage = this->strength;
		this->level = lvl;
	}
}

Character::Character()
{
	this->strength = 0;
	this->defence = 0;
	this->vitality = 0;
	this->gold = 0;
	this->level = 0;
}

long long int Character::getStr()
{
	return this->strength;
}

long long int Character::getDef()
{
	return this->defence;
}

long long int Character::getVit()
{
	return this->vitality;
}

long long int Character::getGold()
{
	return this->gold;
}

long long int Character::getLvl()
{
	return this->level;
}

long long int Character::getHealth()
{
	return this->health;
}

long long int Character::getMaxHealth()
{
	return this->maxHealth;
}

long long int Character::getDamage()
{
	return this->damage;
}

void Character::subHealth(long long int a)
{
	this->health -= a;
}

void Character::addHealth(long long int a)
{
	this->health += a;
}

float Character::getDamageReduction(Character enemy)
{
	float DR = (float)this->getDef() / ((float)this->getDef() + 8 + 5*enemy.getLvl());
	std::cout << DR;
	return DR;
}

void Character::setHealth()
{
	this->maxHealth = this->vitality * 3;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
}

void Character::setStr(long long int a)
{
	this->strength = a;
	this->damage = this->strength;
}

void Character::setDef(long long int a)
{
	this->defence = a;
}

void Character::setVit(long long int a)
{
	this->vitality = a;
	this->setHealth();
}

void Character::setGold(long long int a)
{
	this->gold = a;
}

void Character::addGold(long long int a)
{
	this->gold += a;
}

void Character::setLvl(long long int a)
{
	this->level = a;
}

void Character::setHealth(long long int a)
{
	this->health = a;
}