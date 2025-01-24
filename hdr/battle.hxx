#ifndef BATTLE_H
#define BATTLE_H

#include "being.hxx"

void addToTimeline(std::vector<Being *> &timeline, Being &being);
void startBattle(std::vector<Being *> allyArr, std::vector<Being *> enemyArr);

#endif
