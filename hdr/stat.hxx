#ifndef STAT_H
#define STAT_H

#include "pch.hxx"

struct Status {
	bool alive = true;
	bool onDeathDoor = false;
	int8_t burnStack;  // Damage over time
	short burnGauge;
	int8_t freezeStack;  // Increase AP cost
	short freezeGauge;
};

struct Stats {
	int SP;    // Shield Point
	int HP;    // HealtH Point
	int ATK;   // Attack
	int DEF;   // Defense

	short TD;  // Turn Delay
};

#endif
