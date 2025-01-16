#include <fstream>
#include <string>

#include "character.hxx"

Character::Character(std::string name): m_name(name), base(), current() {
		std::ifstream file("src/data/characters/" + name);
		file >> base.HP >> base.EP;
		statInit();
		fullRecovery();
	}

void Character::baseAttack(Character enemy) {
	int dmg = current.ATK - enemy.current.DEF;
	if (dmg < 0) {
		dmg = 0;
	}
	enemy.current.HP -= dmg;
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
	if (charge > 200) {
		charge = 200;
	}
}

unsigned short Character::isUltReady() const {
	if (charge == 200) return 2;
	if (charge >= 100) return 1;
	return 0;
}

void Character::statInit() {
	m_maxHP = base.HP * m_lvl;
	m_maxEP = base.EP * m_lvl;
}
