#include <string>
#include <vector>

#include "being.hxx"
#include "skill.hxx"

Skill::Skill(const std::string &id, Being *self): self(self) {
}

void Skill::mod(Being *target, const Param &side) {
	(*target).current.HP += side.modAmountHP;
	(*target).maxHP += side.modAmountHP;
	(*target).current.ATK += side.modAmountATK;
	(*target).current.DEF += side.modAmountDEF;
}

void Skill::executeParty(std::vector<Being *> &party, const Param &side) {
	if (side.modifier) {
		if (side.targetRequired) {
			mod(party[side.targetIdx], side);
			for (short i = 1; i <= side.range; ++i) {
				mod(party[side.targetIdx + i], side);
				mod(party[side.targetIdx - i], side);
			}
		} else {
			mod(self, side);
		}
	}
	if (side.heal) {
		if (side.targetRequired) {
			party[side.targetIdx]->heal(side.healAmount);
			for (short i = 1; i <= side.range; ++i) {
				party[side.targetIdx + i]->heal(side.healAmount);
				party[side.targetIdx - i]->heal(side.healAmount);
			}
		} else {
			self->heal(side.healAmount);
		}
	}
	if (side.shield) {
		if (side.targetRequired) {
			party[side.targetIdx]->shield(side.shieldAmount);
			for (short i = 1; i <= side.range; ++i) {
				party[side.targetIdx + i]->shield(side.shieldAmount);
				party[side.targetIdx - i]->shield(side.shieldAmount);
			}
		} else {
			self->shield(side.shieldAmount);
		}
	}
	if (side.damage && side.targetRequired) {
		self->attack(*party[side.targetIdx], side.pcATK);
		for (short i = 1; i <= side.range; ++i) {
			self->attack(*party[side.targetIdx + i], side.pcATK);
			self->attack(*party[side.targetIdx - i], side.pcATK);
		}
	}
}

void Skill::execute(std::vector<Being *> &allyParty, std::vector<Being *> &enemyParty) {
	if (onAlly) executeParty(allyParty, ally);
	if (onEnemy) executeParty(enemyParty, enemy);
	if (skillType == "delay") onDelay = true;
}
