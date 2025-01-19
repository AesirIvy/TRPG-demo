#ifndef BEING_H
#define BEING_H

#include "stat.hxx"

class Being {
public:
	bool alive = true;
	unsigned int m_lvl = 1;

	Stats base;
	Stats current;

	void basicAttack(Being& enemy);
	virtual void receiveDmg(int amount) = 0;
	bool statInitFromFile(std::string filePath);
	void statRefresh();

	Being(std::string name);
	virtual ~Being();

protected:
	std::string m_name;
	int m_maxHP;
	int m_maxEP;
};

class Creature: public Being {
public:
	Creature(std::string name);

	void fullRecovery();
	void receiveDmg(int amount);
};

class Character: public Being {
public:
	short charge;
	unsigned int status;

	Character(std::string name);

	void battleInit();
	void checkLvlUp();
	void fullRecovery();
	void heal(int amount);
	void increaseSP(int amount);
	void increaseCharge(int amount);
	bool isOnDeathDoor() const;
	unsigned short isUltReady() const;
	void receiveDmg(int amount);

private:
	int m_recoveryGauge;
	unsigned int m_exp = 0;
};

#endif
