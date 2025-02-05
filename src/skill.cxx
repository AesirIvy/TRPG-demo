#include <unordered_map>

#include "skill.hxx"
#include "status.hxx"

skillFuncPtr findSkill(
	const std::string &id,
	uint8_t targetIdx,
	Being &self,
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty,
) {
	std::unordered_map skillMap = {
		{"megarana-base-attack"}, {megaranaBaseAttack)}
	}
}

megaranaBaseAttack(
	uint8_t targetIdx,
	Being &self,
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty,
) {
	Status poison("poison", 1);
	self.attack(enemyParty[targetIdx], 60);
	self.AP -= 30;
	enemyParty[targetIdx].statusVect.push_back(poison);
}
