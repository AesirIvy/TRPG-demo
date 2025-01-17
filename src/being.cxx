#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "being.hxx"

Being::Being(std::string name): m_name(name), base(), current() {

}

void Being::baseAttack(auto enemy) {
	int dmg = current.ATK - enemy.current.DEF;
	if (dmg > 0) {
		enemy.receiveDmg(dmg);
	}
}

void Being::statInit() {
	m_maxHP = base.HP * m_lvl;
	m_maxEP = base.EP * m_lvl;
}

Character::Character(std::string name): Being(name) {
	std::ifstream file("src/data/being/characters.csv");
	std::string line;
	while (std::getline(file, line)) {
		bool nextLoop = false;
		std::string token;
		std::stringstream ss(line);
		std::vector<std::string> tokens;
		while (std::getline(ss, token, '\t')) {
			if (token != name) {
				nextLoop = true;
				break;
			} else {
				continue;
			}
			tokens.push_back(token);
		}
		if (nextLoop) continue;
		if (tokens[0] == name) {
			base.HP = std::stoi(tokens[1]);
			base.ATK = std::stoi(tokens[2]);
			base.DEF = std::stoi(tokens[3]);
			statInit();
			fullRecovery();
			return;
		}
	}
	std::cout << name << " not fount in database" << std::endl;
}

void Character::battleInit() {
	charge = 0;
}

void Character::checkLvlUp() {
	int expRequired = 150 * m_lvl;
	if (m_exp >= expRequired) {
		m_lvl += 1;
		m_exp -= expRequired;
		statInit();
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
	std::ifstream file("src/data/being/creatures.csv");
	std::string line;
	while (std::getline(file, line)) {
		bool nextLoop = false;
		std::string token;
		std::stringstream ss(line);
		std::vector<std::string> tokens;
		while (std::getline(ss, token, '\t')) {
			if (token != name) {
				nextLoop = true;
				break;
			} else {
				continue;
			}
			tokens.push_back(token);
		}
		if (nextLoop) continue;
		if (tokens[0] == name) {
			base.HP = std::stoi(tokens[1]);
			base.ATK = std::stoi(tokens[2]);
			base.DEF = std::stoi(tokens[3]);
			statInit();
			fullRecovery();
			return;
		}
	}
	std::cout << name << " not fount in database" << std::endl;
}

void Creature::fullRecovery() {
	current.HP = m_maxHP;
	current.EP = m_maxEP;
}

void Creature::receiveDmg(int amount) {
	current.HP -= amount;
}
