#pragma once
#include "Character.h"
#include "headers.h"

struct Item {
	short type;
	long long int strength;
	long long int magic;
	long long int defence;
	long long int vitality;
	long long int luck;
};

class Player : public Character
{
protected:

	long long int magic;
	long long int luck;
	long long int statPoints;
	int experience = 0;
	int maxExperience = 1000;

public:

	Item equipment[EQUIPMENT_SIZE];
	Item backpack[BACKPACK_SIZE];


	Player(long long int str, long long int magic, long long int def, long long int vit, long long int luck, long long int lvl, long long int gold);
	Player();

	~Player();

	long long int getMag();
	long long int getLuck();
	long long int getLvl();
	long long int getStatPts();

	void decStatPts();

	void setMag(long long int a);
	void setLuck(long long int a);
	void addExp(int a);
	void lvlUp();
	void setStatPts(long long int a);

	void initEq();

	bool canEquip(short slot);

	void removeFromBackpack(short slot);

	short findEmptyBackpackSlot();
	bool addToBackpack(Item i);
	void swapItem(short eqSlot, short bpSlot);

	void equipItem(short slot);
	void unEquipItem(short type);

	void sellItem(short type);
};

