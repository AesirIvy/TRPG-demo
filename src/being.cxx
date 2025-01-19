#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "being.hxx"

Being::Being(std::string name): m_name(name), base(), current() {

}

Being::~Being() {

}

void Being::basicAttack(Being& enemy) {
	int dmg = current.ATK - enemy.current.DEF;
	if (dmg > 0) {
		enemy.receiveDmg(dmg);
	}
}

bool Being::statInitFromFile(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	while (std::getline(file, line)) {
		bool nextLoop = false;
		std::string token;
		std::stringstream ss(line);

		std::getline(ss, token, '\t');
		if (token != m_name) {
			continue;
		}

		std::getline(ss, token, '\t');
		base.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		base.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		base.DEF = std::stoi(token);

		statRefresh();
		return true;
	}
	std::cout << m_name << " not found in database" << std::endl;
	return false;
}

void Being::statRefresh() {
	m_maxHP = base.HP * m_lvl;
	m_maxEP = base.EP * m_lvl;
	current.ATK = base.ATK * m_lvl;
	current.DEF = base.DEF * m_lvl;
}

Character::Character(std::string name): Being(name) {
	if (statInitFromFile("src/data/being/character.csv")) {
		fullRecovery();
	};
}

void Character::battleInit() {
	charge = 0;
}

void Character::checkLvlUp() {
	int expRequired = 150 * m_lvl;
	if (m_exp >= expRequired) {
		m_lvl += 1;
		m_exp -= expRequired;
		statRefresh();
	}
}

void Character::fullRecovery() {
	current.HP = m_maxHP;
	current.EP = m_maxEP;
	m_recoveryGauge = m_maxHP;
}

void Character::heal(int amount) {
	current.HP += amount;
	if (current.HP > m_maxHP) {
		current.HP = m_maxHP;
	}
}

void Character::increaseSP(int amount) {
	current.SP += amount;
	if (current.SP > m_maxHP) {
		current.SP = m_maxHP;
	}
}

void Character::increaseCharge(int amount) {
	charge += amount;
	if (charge > 300) {
		charge = 300;
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
	if (isOnDeathDoor()) {
		alive = false;
	}
	m_recoveryGauge = current.HP;
	current.HP -= amount;
}

Creature::Creature(std::string name): Being(name) {
	if (statInitFromFile("src/data/being/creature.csv")) {
		fullRecovery();
	};
}

void Creature::fullRecovery() {
	current.HP = m_maxHP;
	current.EP = m_maxEP;
}

void Creature::receiveDmg(int amount) {
	current.HP -= amount;
}
