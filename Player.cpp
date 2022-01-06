#include "Player.h"
#include "headers.h"

Player::Player(long long int str, long long int magic, long long int def, long long int vit, long long int luck, long long int lvl, long long int gold) :Character(str, def, vit, gold, lvl)
{
	this->luck = luck;
	this->level = lvl;
	this->magic = magic;
	this->setHealth();
	this->damage = this->strength;
	this->initEq();
	this->statPoints = 5;
}

Player::Player() {}

long long int Player::getMag()
{
	return this->magic;
}

long long int Player::getLuck()
{
	return this->luck;
}

long long int Player::getLvl()
{
	return this->level;
}

long long int Player::getStatPts()
{
	return this->statPoints;
}

void Player::decStatPts()
{
	this->statPoints--;
}

void Player::setMag(long long int a)
{
	this->magic = a;
}

void Player::setLuck(long long int a)
{
	this->luck = a;
}

void Player::addExp(int a)
{
	this->experience += a;
	if (this->experience == 1000) this->lvlUp();
	else if (this->experience > 1000)
	{
		int diff = this->experience - 1000;
		this->lvlUp();
		this->experience = diff;
	}
}

void Player::lvlUp()
{
	this->level++;
	this->statPoints += 5;
	this->experience = 0;
}

void Player::setStatPts(long long int a)
{
	this->statPoints = a;
}

void Player::initEq()
{
	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		equipment[i].type = -1;
		equipment[i].strength = 0;
		equipment[i].magic = 0;
		equipment[i].defence = 0;
		equipment[i].vitality = 0;
		equipment[i].luck = 0;
	}
	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		backpack[i].type = -1;
		backpack[i].strength = 0;
		backpack[i].magic = 0;
		backpack[i].defence = 0;
		backpack[i].vitality = 0;
		backpack[i].luck = 0;
	}
}


bool Player::canEquip(short slot)
{
	if (
		this->equipment[backpack[slot].type].type == -1 &&
		(this->strength + backpack[slot].strength) >= 0 &&
		(this->magic + backpack[slot].magic) >= 0 &&
		(this->defence + backpack[slot].defence) >= 0 &&
		(this->vitality + backpack[slot].vitality) >= 0 &&
		(this->luck + backpack[slot].luck) >= 0
		) return true;
	else return false;
}

void Player::removeFromBackpack(short slot)
{
	backpack[slot].type = -1;
	backpack[slot].strength = 0;
	backpack[slot].magic = 0;
	backpack[slot].defence = 0;
	backpack[slot].vitality = 0;
	backpack[slot].luck = 0;
}

void Player::equipItem(short slot)
{
	if (canEquip(slot))
	{
		this->equipment[backpack[slot].type].type = backpack[slot].type;
		this->equipment[backpack[slot].type].strength = backpack[slot].strength;
		this->equipment[backpack[slot].type].magic = backpack[slot].magic;
		this->equipment[backpack[slot].type].defence = backpack[slot].defence;
		this->equipment[backpack[slot].type].vitality = backpack[slot].vitality;
		this->equipment[backpack[slot].type].luck = backpack[slot].luck;

		this->setStr(this->strength + backpack[slot].strength);
		this->setMag(this->magic + backpack[slot].magic);
		this->setDef(this->defence + backpack[slot].defence);
		this->setVit(this->vitality + backpack[slot].vitality);
		this->setLuck(this->luck + backpack[slot].luck);
		this->removeFromBackpack(slot);
	}
}

short Player::findEmptyBackpackSlot()
{
	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		if (this->backpack[i].type == -1) return i;
	}
	return -1;
}

bool Player::addToBackpack(Item item)
{
	short place = this->findEmptyBackpackSlot();
	if(place != -1)
	{
		this->backpack[place].type = item.type;
		this->backpack[place].strength = item.strength;
		this->backpack[place].magic = item.magic;
		this->backpack[place].defence = item.defence;
		this->backpack[place].vitality = item.vitality;
		this->backpack[place].luck = item.luck;
		return true;
	}
	else return false;
}

void Player::swapItem(short eqSlot, short bpSlot)
{
	if (this->backpack[bpSlot].type == this->equipment[eqSlot].type || this->backpack[bpSlot].type == -1)
	{
		Item tmp = this->equipment[eqSlot];

		this->setStr(this->strength - equipment[eqSlot].strength);
		this->setMag(this->magic - equipment[eqSlot].magic);
		this->setDef(this->defence - equipment[eqSlot].defence);
		this->setVit(this->vitality - equipment[eqSlot].vitality);
		this->setLuck(this->luck - equipment[eqSlot].luck);

		this->equipment[eqSlot] = this->backpack[bpSlot];

		this->setStr(this->strength + equipment[eqSlot].strength);
		this->setMag(this->magic + equipment[eqSlot].magic);
		this->setDef(this->defence + equipment[eqSlot].defence);
		this->setVit(this->vitality + equipment[eqSlot].vitality);
		this->setLuck(this->luck + equipment[eqSlot].luck);
		this->backpack[bpSlot] = tmp;
	}
}

void Player::unEquipItem(short type)
{
	if (equipment[type].type != -1)
	{
		if (this->addToBackpack(this->equipment[type]) == true)
		{
			this->setStr(this->strength - equipment[type].strength);
			this->setMag(this->magic - equipment[type].magic);
			this->setDef(this->defence - equipment[type].defence);
			this->setVit(this->vitality - equipment[type].vitality);
			this->setLuck(this->luck - equipment[type].luck);
			this->equipment[type] = { -1, 0, 0, 0, 0, 0 };
		}
	}
}

void Player::sellItem(short type)
{
	long long int sum = 0;
	sum = equipment[type].strength + equipment[type].magic + equipment[type].defence + equipment[type].vitality + equipment[type].luck;
	this->backpack[type] = {-1, 0, 0, 0, 0, 0 };
	this->addGold(sum);
}

Player::~Player()
{
	//dtor
}
