#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

#include "stat.hxx"

class Equipment {
public:
	std::string name;

	Stats increment;

	void statInitFromFile(std::string file_path);
	explicit Equipment(const std::string &name);
	virtual ~Equipment() = default;
};

class Artifact: public Equipment {
public:
	explicit Artifact(const std::string &name);
};

class Weapon: public Equipment {
public:
	explicit Weapon(const std::string &name);
};

#endif
