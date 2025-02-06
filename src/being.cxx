#include <fstream>
#include <sstream>

#include "being.hxx"
#include "util.hxx"

Being::Being(const std::string &id): id(id), base(), current() {

}

void Being::battleStatRefresh() {
	if (maxHP == 0) return;
	int percentageHP = current.HP / maxHP;
	current.ATK = base.ATK * percentageHP;
	current.DEF = base.DEF * percentageHP;
}

void Being::attack(Being &enemy, int pcATK) {
	int dmg = current.ATK * pcATK - enemy.current.DEF;
	if (dmg < 0) dmg = 0;
	enemy.receiveDmg(dmg);
}

void Being::heal(int amount) {
	current.HP += amount;
	if (current.HP > maxHP) {
		current.HP = maxHP;
	}
}

void Being::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	current.SP -= dmg;
	if (current.SP < 0) {
		current.HP += current.SP;
		current.SP = 0;
	}
	if (current.HP <= 0) alive = false;
	else battleStatRefresh();
}

void Being::shield(int amount) {
	current.SP += amount;
}

Character::Character(const std::string &id): Being(id) {
	statInitFromFile();
	fullRecovery();
}

void Character::attack(Being &enemy, int pcATK) {
	int dmg = current.ATK * pcATK * (current.HP / maxHP) - enemy.current.DEF;
	if (dmg < 0) dmg = 0;
	else increaseDP(5);
	enemy.receiveDmg(dmg);
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

void Character::heal(int amount) {
	current.HP += amount;
	if (current.HP > recoveryGauge) {
		current.HP -= (current.HP - recoveryGauge) / 2;
		recoveryGauge = current.HP;
	}
	if (current.HP > maxHP) {
		current.HP = maxHP;
	}
}

void Character::increaseDP(int amount) {
	DP += amount;
	if (DP > 100) DP = 100;
}

void Character::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	else increaseDP(5);

	if (dmg <= 0) return;

	current.SP -= dmg;
	if (current.SP < 0) {
		recoveryGauge = current.HP;
		current.HP += current.SP;
		current.SP = 0;
	}
	if (current.HP <= 0 && onDeathDoor) alive = false;
	else if (current.HP <= 0) onDeathDoor = true;
	else battleStatRefresh();
}

void Character::statInitFromFile() {
	std::istringstream iss = dataFromCSV("src/data/being/character.csv", id);
	if (iss.peek() == EOF) throw std::invalid_argument(id + " not found in database\n");

	std::string token;

	std::getline(iss, token, '\t');
	name = token;
	std::getline(iss, token, '\t');
	base.HP = std::stoi(token);
	std::getline(iss, token, '\t');
	base.ATK = std::stoi(token);
	std::getline(iss, token, '\t');
	base.DEF = std::stoi(token);
	std::getline(iss, token, '\t');
	base.TD = std::stoi(token);

	std::getline(iss, token, '\t');
	passive = findSkill(token);

	statRefresh();
}

void Character::statRefresh() {
	maxSP = base.SP;
	maxHP = base.HP;
	current.ATK = base.ATK + weapon.increment.ATK;
	current.DEF = base.DEF + weapon.increment.DEF;
}

Creature::Creature(const std::string &id): Being(id) {
	statInitFromFile();
	fullRecovery();
}

void Creature::attack(Being &enemy, int pcATK) {
	int dmg = current.ATK * pcATK * (current.HP / maxHP) - enemy.current.DEF;
	if (dmg < 0) dmg = 0;
	enemy.receiveDmg(dmg);
}

void Creature::fullRecovery() {
	current.HP = maxHP;
	recoveryGauge = maxHP;
}

void Creature::heal(int amount) {
	current.HP += amount;
	if (current.HP > recoveryGauge) {
		current.HP -= (current.HP - recoveryGauge) / 2;
		recoveryGauge = current.HP;
	}
	if (current.HP > maxHP) {
		current.HP = maxHP;
	}
}

void Creature::statInitFromFile() {
	std::istringstream iss = dataFromCSV("src/data/being/creature.csv", id);
	if (iss.peek() == EOF) throw std::invalid_argument(id + " not found in database\n");

	std::string token;

	std::getline(iss, token, '\t');
	name = token;
	std::getline(iss, token, '\t');
	base.HP = std::stoi(token);
	std::getline(iss, token, '\t');
	base.ATK = std::stoi(token);
	std::getline(iss, token, '\t');
	base.DEF = std::stoi(token);
	std::getline(iss, token, '\t');
	base.TD = std::stoi(token);

	std::getline(iss, token, '\t');
	passive = findSkill(token);

	statRefresh();
}

void Creature::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	current.SP -= dmg;
	if (current.SP < 0) {
		recoveryGauge = current.HP;
		current.HP += current.SP;
		current.SP = 0;
	}
	if (current.HP <= 0) alive = false;
	else battleStatRefresh();
}

void Creature::statRefresh() {
	maxSP = base.SP;
	maxHP = base.HP;
	current.ATK = base.ATK;
	current.DEF = base.DEF;
	current.TD = base.TD;
}

Machine::Machine(const std::string &id): Being(id) {
	statInitFromFile();
	fullRecovery();
}

void Machine::fullRecovery() {
	current.SP = maxSP;
}

void Machine::receiveDmg(int dmg) {
	if (!exposed) dmg *= 1.5;  // critical damage for being off-guard
	current.SP -= dmg;
	if (current.SP <= 0) alive = false;
}

void Machine::shield(int amount) {
	current.SP += amount;
	if (current.SP > maxSP) {
		current.SP = maxSP;
	}
}

void Machine::statInitFromFile() {
	std::istringstream iss = dataFromCSV("src/data/being/machine.csv", id);
	if (iss.peek() == EOF) throw std::invalid_argument(id + " not found in database\n");

	std::string token;

	std::getline(iss, token, '\t');
	name = token;
	std::getline(iss, token, '\t');
	base.SP = std::stoi(token);
	std::getline(iss, token, '\t');
	base.ATK = std::stoi(token);
	std::getline(iss, token, '\t');
	base.DEF = std::stoi(token);
	std::getline(iss, token, '\t');
	base.TD = std::stoi(token);

	std::getline(iss, token, '\t');
	passive = findSkill(token);

	statRefresh();
}

void Machine::statRefresh() {
	maxSP = base.SP;
	maxHP = base.HP;
	current.ATK = base.ATK;
	current.DEF = base.DEF;
	current.TD = base.TD;
}
