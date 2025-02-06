#ifndef STAT_H
#define STAT_H

#include "pch.hxx"

struct Stat {
	int SP;    // Shield Point
	int HP;    // HealtH Point
	int ATK;   // Attack
	int DEF;   // Defense

	short TD;  // Turn Delay

	Stat(): SP(0), HP(0), ATK(0), DEF(0), TD(0) {};
};

#endif  // STAT_H
