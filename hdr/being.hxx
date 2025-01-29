#ifndef BEING_H
#define BEING_H

#include "pch.hxx"

#include "equipment.hxx"
#include "stat.hxx"

class Being {
public:
	bool alive = true;
	bool exposed = false;
	bool playerSide = true;
	int maxHP;
	int recoveryGauge;
	short IP = 0;  // Initiative Point
	std::string id;
	std::string name;

	Stats base;
	Stats current;

	void battleStatRefresh();
	void statInitFromFile(std::string filePath);

	virtual void attack(Being &enemy, int pcATK);
	virtual void heal(int amount);
	virtual void receiveDmg(int dmg);
	virtual void shield(int amount);

protected:
	explicit Being(const std::string &id);
	virtual ~Being() = default;
};

class Creature: public Being {
public:
	explicit Creature(const std::string &id);

	void fullRecovery();
};

class Character: public Being {
public:
	short DP = 0;  // Determination Point
	unsigned int status;

	Artifact artifact = Artifact("None");
	Weapon weapon = Weapon("None");

	explicit Character(const std::string &id);

	void attack(Being &enemy, int pcATK) override;
	void battleInit();
	void equip(const Equipment &equipment);
	void fullRecovery();
	void increaseDP(int amount);
	bool isOnDeathDoor() const;
	bool isUltReady() const;
	void receiveDmg(int dmg) override;
	void statRefresh();
};

#endif
