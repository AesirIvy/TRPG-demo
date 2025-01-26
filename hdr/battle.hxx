#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

#include "being.hxx"

void addToTimeline(std::vector<Being *> &timeline, Being &being);
void startBattle(const std::vector<Being *> &allyArr, const std::vector<Being *> &enemyArr);

#endif
