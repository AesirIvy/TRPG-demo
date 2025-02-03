#ifndef STATUS_H
#define STATUS_H

#include "pch.hxx"

class Being;

class Status {
public:
	std::string name;  // the name acts as the id

	uint8_t stack;

	int amount;
	bool isDamage;  // reduce HP
	bool isLeak;    // reduce AP

	Status(std::string name, uint8_t stack);
};

class StatusManager {
public:
	void addStatus(Status &status);
	void resolveStatus(Being &being);
private:
	std::vector<Status> statusVec;
};

#endif
