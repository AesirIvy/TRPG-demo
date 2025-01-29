#ifndef SKILL_H
#define SKILL_H

#include "pch.hxx"

#include "being.hxx"

struct Param {
	// pc: percentage

	bool targetRequired;
	unsigned short targetIdx;

	unsigned short range;

	bool modifier;
	int modAmountHP;
	int modAmountATK;
	int modAmountDEF;

	bool heal;
	int healAmount;

	bool shield;
	int shieldAmount;

	bool damage;
	int pcATK;
};

class Skill {
public:
	std::string skillType;

	bool onDelay;

	bool onAlly;
	bool onEnemy;

	Param ally;
	Param enemy;

	Skill(const std::string &id, Being *self);
	void execute(std::vector<Being *> &allyParty, std::vector<Being *> &enemyParty);
private:
	Being *self;

	void executeParty(std::vector<Being *> &party, const Param &side);
	void mod(Being *target, const Param &side);
};


#endif
