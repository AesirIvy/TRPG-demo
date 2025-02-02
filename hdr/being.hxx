#ifndef BEING_H
#define BEING_H

#include "pch.hxx"

#include "equipment.hxx"
#include "stat.hxx"

class Being {
public:
	bool alive = true;
	bool exposed = false;
	int maxSP = 0;
	int maxHP = 0;
	short IP = 0;  // Initiative Point
	std::string id;
	std::string name;

	Status immune;
	Status affected;

	Stats base;
	Stats current;

	void battleStatRefresh();

	virtual void attack(Being &enemy, int pcATK);
	virtual void heal(int amount);
	virtual void receiveDmg(int dmg);
	virtual void shield(int amount);
	virtual void statInitFromFile(std::string filePath);

protected:
	explicit Being(const std::string &id);
	virtual ~Being() = default;
};

/*
 * Character is intended to be played by the user,
 * while Creature and Machine act on their own.
 */

class Character: public Being {
public:
	short DP = 0;  // Determination Point
	int recoveryGauge;
	unsigned int status;

	Artifact artifact = Artifact("None");
	Weapon weapon = Weapon("None");

	explicit Character(const std::string &id);

	void attack(Being &enemy, int pcATK) override;
	void battleInit();
	void equip(const Equipment &equipment);
	void fullRecovery();
	void heal(int amount) override;
	void increaseDP(int amount);
	bool isOnDeathDoor() const;
	bool isUltReady() const;
	void receiveDmg(int dmg) override;
	void statRefresh();
};

class Creature: public Being {
public:
	int recoveryGauge;

	explicit Creature(const std::string &id);

	void attack(Being &enemy, int pcATK) override;
	void fullRecovery();
	void heal(int amount) override;
	void receiveDmg(int dmg) override;
};

class Machine: public Being {
public:
	explicit Machine(const std::string &id);

	void fullRecovery();
	void receiveDmg(int dmg) override;
	void statInitFromFile(std::string filePath) override;
};

#endif
