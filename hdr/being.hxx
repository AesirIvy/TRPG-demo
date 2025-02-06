#ifndef BEING_H
#define BEING_H

#include "pch.hxx"

#include "equipment.hxx"
#include "skill.hxx"
#include "stat.hxx"
#include "status.hxx"

class Being {
public:
	bool alive = true;
	bool exposed = false;
	int maxSP = 0;
	int maxHP = 0;
	short AP = 0;
	short IP = 0;  // Initiative Point
	std::string id;
	std::string name;

	Stat base;
	Stat current;

	skillFuncPtr passive;

	std::vector<Status> statusVec;

	void battleStatRefresh();

	virtual void attack(Being &enemy, int pcATK);
	virtual void heal(int amount);
	virtual void receiveDmg(int dmg);
	virtual void shield(int amount);

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
	bool onDeathDoor = false;
	short DP = 0;  // Determination Point
	int recoveryGauge;

	Artifact artifact = Artifact("None");
	Weapon weapon = Weapon("None");

	explicit Character(const std::string &id);

	void attack(Being &enemy, int pcATK) override;
	void equip(const Equipment &equipment);
	void fullRecovery();
	void heal(int amount) override;
	void increaseDP(int amount);
	void receiveDmg(int dmg) override;
	void statInitFromFile();
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
	void statInitFromFile();
	void statRefresh();
};

class Machine: public Being {
public:
	explicit Machine(const std::string &id);

	void fullRecovery();
	void receiveDmg(int dmg) override;
	void shield(int amount) override;
	void statInitFromFile();
	void statRefresh();
};

#endif  // BEING_H
