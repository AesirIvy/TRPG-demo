#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

#include "stat.hxx"

class Equipment {
public:
	std::string name;

	Stats increment;

	void statInitFromFile(std::string file_path);
	Equipment(std::string name);
};

class Artifact: public Equipment {
public:
	Artifact(std::string name);
};

class Weapon: public Equipment {
public:
	Weapon(std::string name);
};

#endif
