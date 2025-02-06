#ifndef STATUS_H
#define STATUS_H

#include "pch.hxx"

class Status {
public:
	std::string name;  // the name acts as the id

	uint8_t stack;

	int amount;
	bool isDamage;  // reduce HP
	bool isLeak;    // reduce AP
	bool isSlow;    // reduce IP

	Status(std::string name, uint8_t stack);
};

#endif  // STATUS_H
