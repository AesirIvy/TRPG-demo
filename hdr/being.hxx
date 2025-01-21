#ifndef BEING_H
#define BEING_H

#include "equipment.hxx"
#include "stat.hxx"

class Being {
public:
	bool alive = true;

	Stats base;
	Stats current;

	void basicAttack(Being& enemy);
	virtual void receiveDmg(int amount) = 0;
	bool statInitFromFile(std::string filePath);
	virtual void statRefresh();

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
	void receiveDmg(int amount) override;
};

class Character: public Being {
public:
	short charge;
	unsigned int status;

	Weapon weapon;

	Character(std::string name);

	void battleInit();
	void equip(std::string name);
	void fullRecovery();
	void heal(int amount);
	void increaseSP(int amount);
	void increaseCharge(int amount);
	bool isOnDeathDoor() const;
	unsigned short isUltReady() const;
	void receiveDmg(int amount) override;
	void statRefresh() override;

private:
	int m_recoveryGauge;
};

#endif
