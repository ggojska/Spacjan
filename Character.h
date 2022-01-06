#pragma once
class Character {

protected:

	long long int strength;
	long long int defence;
	long long int vitality;
	long long int gold;
	long long int level;
	long long int health;
	long long int maxHealth;
	long long int damage;

public:

	Character(long long int str, long long int def, long long int vit, long long int gold, long long int lvl);
	Character(long long int lvl, short type);
	Character();

	long long int getStr();
	long long int getDef();
	long long int getVit();
	long long int getGold();
	long long int getLvl();
	long long int getHealth();
	long long int getMaxHealth();
	long long int getDamage();

	float getDamageReduction(Character enemy);

	void subHealth(long long int a);
	void addHealth(long long int a);
	virtual long long int getLuck() { return 0; };
	virtual void addExp(int a) {};

	void setHealth();

	void setStr(long long int a);
	void setDef(long long int a);
	void setVit(long long int a);
	void setGold(long long int a);
	void addGold(long long int a);
	void setLvl(long long int a);
	void setHealth(long long int a);

};


