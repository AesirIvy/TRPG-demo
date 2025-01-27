#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "being.hxx"

Being::Being(const std::string &id): id(id), base(), current() {

}

void Being::basicAttack(Being &enemy) {
	int dmg = current.ATK - enemy.current.DEF;
	if (dmg > 0) {
		enemy.receiveDmg(dmg);
	}
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

void Being::battleStatRefresh() {
	int percentageHP = current.HP / maxHP;
	current.ATK = base.ATK * percentageHP;
	current.DEF = base.DEF * percentageHP;
}

Character::Character(const std::string &id): Being(id) {
	statInitFromFile("src/data/being/character.csv");
	fullRecovery();
}

void Character::battleInit() {
	DP = 0;
}

void Character::depriveArtifact() {
	artifact = Artifact("None");
	statRefresh();
}

void Character::depriveWeapon() {
	weapon = Weapon("None");
	statRefresh();
}

void Character::equip(const Equipment &equipment) {
	if (const Artifact *artifactPtr = dynamic_cast<const Artifact *>(&equipment)) {
		artifact = *artifactPtr;
	} else if (const Weapon *weaponPtr = dynamic_cast<const Weapon *>(&equipment)) {
		weapon = *weaponPtr;
	}
}

void Character::fullRecovery() {
	current.HP = maxHP;
	recoveryGauge = maxHP;
}

void Character::heal(int amount) {
	current.HP += amount;
	if (current.HP > maxHP) {
		current.HP = maxHP;
	}
}

void Character::increaseDP(int amount) {
	DP += amount;
	if (DP > 100) DP = 100;
}

void Character::increaseSP(int amount) {
	current.SP += amount;
	if (current.SP > maxHP) {
		current.SP = maxHP;
	}
}

bool Character::isOnDeathDoor() const {
	if (current.HP < 0) {
		return true;
	}
	return false;
}

unsigned short Character::isUltReady() const {
	if (DP == 100) return 1;
	return 0;
}

void Character::receiveDmg(int amount) {
	if (!exposed) amount *= 1.5;  // critical damage for being off-guard
	else increaseDP(2);
	if (isOnDeathDoor()) {
		alive = false;
	}
	recoveryGauge = current.HP;
	current.HP -= amount;
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
}

void Creature::receiveDmg(int amount) {
	current.HP -= amount;
}
