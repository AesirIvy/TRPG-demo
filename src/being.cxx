#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "being.hxx"

Being::Being(const std::string &name): name(name), base(), current() {

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
		if (token != name) continue;

		std::getline(ss, token, '\t');
		base.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		base.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		base.DEF = std::stoi(token);
		std::getline(ss, token, '\t');
		base.TD = std::stoi(token);

		m_maxHP = base.HP;
		current.ATK = base.ATK;
		current.DEF = base.DEF;
		current.TD = base.TD;
		return;
	}
	throw std::invalid_argument(name + " not found in database\n");
}

void Being::battleStatRefresh() {
	int percentageHP = current.HP / m_maxHP;
	current.ATK = base.ATK * percentageHP;
	current.DEF = base.DEF * percentageHP;
}

Character::Character(const std::string &name): Being(name) {
	statInitFromFile("src/data/being/character.csv");
	fullRecovery();
}

void Character::battleInit() {
	charge = 0;
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
	current.HP = m_maxHP;
	m_recoveryGauge = m_maxHP;
}

void Character::heal(int amount) {
	current.HP += amount;
	if (current.HP > m_maxHP) {
		current.HP = m_maxHP;
	}
}

void Character::increaseCharge(int amount) {
	charge += amount;
	if (charge > 300) {
		charge = 300;
	}
}

void Character::increaseSP(int amount) {
	current.SP += amount;
	if (current.SP > m_maxHP) {
		current.SP = m_maxHP;
	}
}

bool Character::isOnDeathDoor() const {
	if (current.HP < 0) {
		return true;
	}
	return false;
}

unsigned short Character::isUltReady() const {
	if (charge == 300) return 3;
	if (charge >= 200) return 2;
	if (charge >= 100) return 1;
	return 0;
}

void Character::receiveDmg(int amount) {
	if (!guarding) amount *= 1.5;  // critical damage for being off-guard
	if (isOnDeathDoor()) {
		alive = false;
	}
	m_recoveryGauge = current.HP;
	current.HP -= amount;
}

void Character::statRefresh() {
	m_maxHP = base.HP;
	current.ATK = base.ATK + weapon.increment.ATK;
	current.DEF = base.DEF + weapon.increment.DEF;
}

Creature::Creature(const std::string &name): Being(name) {
	statInitFromFile("src/data/being/creature.csv");
	fullRecovery();
}

void Creature::fullRecovery() {
	current.HP = m_maxHP;
}

void Creature::receiveDmg(int amount) {
	current.HP -= amount;
}
