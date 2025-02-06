#ifndef SKILL_H
#define SKILL_H

#include "pch.hxx"

class Being;

using skillFuncPtr = void (*)(
	uint8_t targetIdx,
	Being &self,
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty
);

skillFuncPtr findSkill(const std::string &id);

#endif  // SKILL_H
