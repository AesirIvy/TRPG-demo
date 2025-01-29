#include <fstream>
#include <iostream>
#include <sstream>

#include "being.hxx"

Being::Being(const std::string &id): id(id), base(), current() {

}

void Being::battleStatRefresh() {
	int percentageHP = current.HP / maxHP;
	current.ATK = base.ATK * percentageHP;
	current.DEF = base.DEF * percentageHP;
}

void Being::statInitFromFile(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	while (std::getline(file, line)) {
		std::string token;
		std::stringstream ss(line);

		std::getline(ss, token, '\t');
		if (token != id) continue;

		std::getline(ss, token, '\t');
		name = token;
		std::getline(ss, token, '\t');
		base.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		base.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		base.DEF = std::stoi(token);
		std::getline(ss, token, '\t');
		base.TD = std::stoi(token);

		maxHP = base.HP;
		current.ATK = base.ATK;
		current.DEF = base.DEF;
		current.TD = base.TD;
		return;
	}
	throw std::invalid_argument(id + " not found in database\n");
}

void Being::attack(Being &enemy, int pcATK) {
	int dmg = current.ATK - current.DEF;
	if (dmg < 0) dmg = 0;
	enemy.receiveDmg(dmg);
}

void Being::heal(int amount) {
	current.HP += amount;
	if (current.HP > recoveryGauge) {
		current.HP = (current.HP - recoveryGauge) / 2;
		recoveryGauge = current.HP;
	}
	if (current.HP > maxHP) {
		current.HP = maxHP;
	}
}

void Being::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	current.SP -= dmg;
	if (current.SP < 0) {
		recoveryGauge = current.HP;
		current.HP += current.SP;
		current.SP = 0;
	}
}

void Being::shield(int amount) {
	current.SP += amount;
}

Character::Character(const std::string &id): Being(id) {
	statInitFromFile("src/data/being/character.csv");
	fullRecovery();
}

void Character::attack(Being &enemy, int pcATK) {
	int dmg = current.ATK - current.DEF;
	if (dmg < 0) dmg = 0;
	else increaseDP(5);
	enemy.receiveDmg(dmg);
}

void Character::battleInit() {
	current.SP = 0;
	DP = 0;
}

void Character::equip(const Equipment &equipment) {
	if (const Artifact *artifactPtr = dynamic_cast<const Artifact *>(&equipment)) {
		artifact = *artifactPtr;
	} else if (const Weapon *weaponPtr = dynamic_cast<const Weapon *>(&equipment)) {
		weapon = *weaponPtr;
	}
	statRefresh();
}

void Character::fullRecovery() {
	current.HP = maxHP;
	recoveryGauge = maxHP;
}

void Character::increaseDP(int amount) {
	DP += amount;
	if (DP > 100) DP = 100;
}

bool Character::isOnDeathDoor() const {
	if (current.HP < 0) {
		return true;
	}
	return false;
}

bool Character::isUltReady() const {
	if (DP == 100) return true;
	return false;
}

void Character::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	else increaseDP(5);
	if (isOnDeathDoor() && dmg > 0) {
		alive = false;
	}
	current.SP -= dmg;
	if (current.SP < 0) {
		recoveryGauge = current.HP;
		current.HP += current.SP;
		current.SP = 0;
	}
}

void Character::statRefresh() {
	maxHP = base.HP;
	current.ATK = base.ATK + weapon.increment.ATK;
	current.DEF = base.DEF + weapon.increment.DEF;
}

Creature::Creature(const std::string &id): Being(id) {
	statInitFromFile("src/data/being/creature.csv");
	fullRecovery();
}

void Creature::fullRecovery() {
	current.HP = maxHP;
	recoveryGauge = maxHP;
}
