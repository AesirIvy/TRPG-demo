#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

class Skill {
public:
	bool targetRequired;
	unsigned short targetIdx;
	std::string skillType;

	bool modifier;
	bool capMaxHP;
	int modAmountHP;
	int modAmountATK;
	int modAmountDEF;
	unsigned short range;

	Skill(std::string id, Being *self);
	void execute(std::vector<Being *> &allyParty, std::vector<Being *> &enemyParty);
private:
	Being *self;

	void mod(Being *target);
};


#endif
