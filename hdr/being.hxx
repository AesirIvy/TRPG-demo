#ifndef BEING_H
#define BEING_H

struct Stats {
	int SP;    // Shield Point
	int HP;    // HealtH Point
	int EP;    // Energy Point
	int ATK;   // Attack
	int DEF;   // Defense
	int SPD;   // Speed
	short CR;  // Critical Rate
};

class Being {
public:
	bool alive = true;
	unsigned int m_lvl;

	Stats base;
	Stats current;

	void baseAttack(auto opponent);
	void statInit();

	Being(std::string name);

protected:
	std::string m_name;
	int m_maxHP;
	int m_maxEP;
};

class Creature : public Being {
public:
	Creature(std::string name);

	void fullRecovery();
	void receiveDmg(int amount);
};

class Character : public Being {
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
