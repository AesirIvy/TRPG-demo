#include <unordered_map>

#include "being.hxx"
#include "skill.hxx"
#include "status.hxx"

void megaranaBaseAttack(
	uint8_t targetIdx,
	Being &self,
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty
) {
	Status poison("Poison", 1);
	self.attack(*enemyParty[targetIdx], 60);
	self.AP -= 30;
	enemyParty[targetIdx]->statusVec.push_back(poison);
}

void none(
	uint8_t targetIdx,
	Being &self,
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty
) {
	return;
}

skillFuncPtr findSkill(const std::string &id) {
	static const std::unordered_map<std::string, skillFuncPtr> skillMap = {
		{"Megarana-BA", megaranaBaseAttack},
		{"None", none}
	};
	try {
		return skillMap.at(id);
	} catch (const std::out_of_range &error) {
		std::cerr << error.what() << std::endl;
		return none;
	}
}
