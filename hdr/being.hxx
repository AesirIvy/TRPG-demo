#ifndef BEING_H
#define BEING_H

#include <string>

#include "equipment.hxx"
#include "stat.hxx"

class Being {
public:
	bool alive = true;
	int IP;  // Initiative Point
	std::string name;

	Stats base;
	Stats current;

	void basicAttack(Being &enemy);
	void battleStatRefresh();
	virtual void receiveDmg(int amount) = 0;
	void statInitFromFile(std::string filePath);

	Being(std::string name);
	virtual ~Being();

protected:
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

	Artifact artifact = Artifact("None");
	Weapon weapon = Weapon("None");

	Character(std::string name);

	void battleInit();
	void depriveArtifact();
	void depriveWeapon();
	void equipArtifact(std::string name);
	void equipWeapon(std::string name);
	void fullRecovery();
	void heal(int amount);
	void increaseSP(int amount);
	void increaseCharge(int amount);
	bool isOnDeathDoor() const;
	unsigned short isUltReady() const;
	void receiveDmg(int amount) override;
	void statRefresh();

private:
	int m_recoveryGauge;
};

#endif
