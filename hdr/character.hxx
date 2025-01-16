#ifndef CHARACTER_H
#define CHARACTER_H

#include <fstream>
#include <string>

struct Stats {
	int SP;  // Shield Point
	int HP;  // HealtH Point
	int EP;  // Energy Point
	int ATK; // Attack
	int DEF; // Defense
	int SPD; // Speed
	short CR;  // Critical Rate
};

class Character {
public:
	short charge;

	Stats base;
	Stats current;

	Character(std::string name);

	void baseAttack(Character enemy);
	void battleInit();
	void checkLvlUp();
	void fullRecovery();
	void heal(int amount);
	void increaseSP(int amount);
	void increaseCharge(int amount);
	unsigned short isUltReady() const;
	void statInit();

private:
	std::string m_name;
	int m_maxHP;
	int m_maxEP;
	unsigned int m_lvl = 1;  // level
	unsigned int m_exp = 0;  // experience
};

#endif
