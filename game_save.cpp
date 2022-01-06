#include "game_save.h"
#include "headers.h"

using namespace std;

struct loadFields
{
	long long int str;
	long long int mag;
	long long int def;
	long long int vit;
	long long int luck;
	long long int gold;
	long long int health;
	long long int level;
	long long int statPts;
};

long long int decToBin(long long int n)
{
	long long int binaryNumber = 0;
	int remainder, i = 1;

	while (n != 0)
	{
		remainder = n % 2;
		n /= 2;
		binaryNumber += remainder * i;
		i *= 10;
	}
	return binaryNumber;
}

int binToDec(long long int n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}

bool canLoadGame()
{
	fstream file;
	file.open("data/save.txt");
	if (!file.is_open())
	{
		return false;
	}
	else return true;
}

Player loadGame()
{
	Player tmp = Player();
	loadFields stats;

	fstream file;
	file.open("data/save.txt", fstream::in);
	//str mag def vit luck gold lvl health statpts
	file >> stats.str;
	file >> stats.mag;
	file >> stats.def;
	file >> stats.vit;
	file >> stats.luck;
	file >> stats.gold;
	file >> stats.level;
	file >> stats.health;
	file >> stats.statPts;

	tmp.setStr(stats.str);
	tmp.setMag(stats.mag);
	tmp.setDef(stats.def);
	tmp.setVit(stats.vit);
	tmp.setLuck(stats.luck);
	tmp.setGold(stats.gold);
	tmp.setLvl(stats.level);
	tmp.setHealth(stats.health);
	tmp.setStatPts(stats.statPts);

	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		file >> tmp.equipment[i].type;
		file >> tmp.equipment[i].strength;
		file >> tmp.equipment[i].magic;
		file >> tmp.equipment[i].defence;
		file >> tmp.equipment[i].vitality; 
		file >> tmp.equipment[i].luck;

		tmp.equipment[i].type = (tmp.equipment[i].type);
		tmp.equipment[i].strength = (tmp.equipment[i].strength);
		tmp.equipment[i].magic = (tmp.equipment[i].magic);
		tmp.equipment[i].defence = (tmp.equipment[i].defence);
		tmp.equipment[i].vitality = (tmp.equipment[i].vitality);
		tmp.equipment[i].luck = (tmp.equipment[i].luck);
	}
	 
	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		file >> tmp.backpack[i].type;
		file >> tmp.backpack[i].strength;
		file >> tmp.backpack[i].magic;
		file >> tmp.backpack[i].defence;
		file >> tmp.backpack[i].vitality;
		file >> tmp.backpack[i].luck;

		tmp.backpack[i].type = (tmp.backpack[i].type);
		tmp.backpack[i].strength = (tmp.backpack[i].strength);
		tmp.backpack[i].magic = (tmp.backpack[i].magic);
		tmp.backpack[i].defence = (tmp.backpack[i].defence);
		tmp.backpack[i].vitality = (tmp.backpack[i].vitality);
		tmp.backpack[i].luck = (tmp.backpack[i].luck);
	}
	file.close();
	return tmp;
}

void saveGame(Player player)
{
	fstream file;
	file.open("data/save.txt", fstream::out);

	file << (player.getStr()) << " ";
	file << (player.getMag()) << " ";
	file << (player.getDef()) << " ";
	file << (player.getVit()) << " ";
	file << (player.getLuck()) << " ";
	file << player.getGold() << " ";
	file << (player.getLvl()) << " ";
	file << (player.getHealth()) << " ";
	file << (player.getStatPts()) << "\n";

	file << "\n";
	for (int i = 0; i < EQUIPMENT_SIZE; i++)
	{
		file << (player.equipment[i].type) << " ";
		file << (player.equipment[i].strength) << " ";
		file << (player.equipment[i].magic) << " ";
		file << (player.equipment[i].defence) << " ";
		file << (player.equipment[i].vitality) << " ";
		file << (player.equipment[i].luck) << "\n";
	}

	file << "\n";
	for (int i = 0; i < BACKPACK_SIZE; i++)
	{
		file << (player.backpack[i].type) << " ";
		file << (player.backpack[i].strength) << " ";
		file << (player.backpack[i].magic) << " ";
		file << (player.backpack[i].defence) << " ";
		file << (player.backpack[i].vitality) << " ";
		file << (player.backpack[i].luck) << "\n";
	}
	file.close();
}
