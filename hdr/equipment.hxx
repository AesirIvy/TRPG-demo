#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

#include "stat.hxx"

class Equipment {
public:
	std::string id;
	std::string name;

	Stats increment;

	void statInitFromFile(std::string file_path);
	explicit Equipment(const std::string &id);
	virtual ~Equipment() = default;
};

class Artifact: public Equipment {
public:
	explicit Artifact(const std::string &id);
};

class Weapon: public Equipment {
public:
	explicit Weapon(const std::string &id);
};

#endif
