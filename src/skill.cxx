#include <string>
#include <vector>

#include "being.hxx"
#include "skill.hxx"

Skill::Skill(std::string id, Being *self): self(self) {
}

void Skill::mod(Being *target) {
	(*target).current.HP += modAmountHP;
	if ((*target).current.HP > (*target).maxHP) {
		if(capMaxHP) (*target).current.HP = (*target).maxHP;
		else (*target).maxHP = (*target).current.HP;
	}
	(*target).current.ATK += modAmountATK;
	(*target).current.DEF += modAmountDEF;
}

void Skill::execute(std::vector<Being *> &allyParty, std::vector<Being *> &enemyParty) {
	if (modifier) {
		if (targetRequired) {
			mod(allyParty[targetIdx]);
			for (short i = 1; i <= range; ++i) {
				mod(allyParty[targetIdx + i]);
				mod(allyParty[targetIdx - i]);
			}
		} else {
			mod(self);
		}
	};
}
