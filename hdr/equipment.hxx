#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "stat.hxx"

class Equipment {
public:
	Stats increment;

	void statInitFromFile(std::string file_path);
	Equipment(std::string name);

protected:
	std::string m_name;
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
