#ifndef BEING_H
#define BEING_H

#include <string>

#include "equipment.hxx"
#include "stat.hxx"

class Being {
public:
	bool alive = true;
	bool exposed = false;
	bool playerSide = true;
	int maxHP;
	short IP = 0;  // Initiative Point
	std::string id;
	std::string name;

	Stats base;
	Stats current;

	void basicAttack(Being &enemy);
	void battleStatRefresh();
	virtual void receiveDmg(int amount) = 0;
	void statInitFromFile(std::string filePath);

	explicit Being(const std::string &id);
	virtual ~Being() = default;
};

class Creature: public Being {
public:
	explicit Creature(const std::string &id);

	void fullRecovery();
	void receiveDmg(int amount) override;
};

class Character: public Being {
public:
	short DP = 0;  // Determination Point
	int recoveryGauge;
	unsigned int status;

	Artifact artifact = Artifact("None");
	Weapon weapon = Weapon("None");

	explicit Character(const std::string &id);

	void battleInit();
	void depriveArtifact();
	void depriveWeapon();
	void equip(const Equipment &equipment);
	void fullRecovery();
	void heal(int amount);
	void increaseSP(int amount);
	void increaseDP(int amount);
	bool isOnDeathDoor() const;
	unsigned short isUltReady() const;
	void receiveDmg(int amount) override;
	void statRefresh();
};

#endif
