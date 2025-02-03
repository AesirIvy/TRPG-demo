#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "pch.hxx"

#include "stat.hxx"

class Equipment {
public:
	std::string id;
	std::string name;

	Stat increment;

	void statInitFromFile(const std::string &file_path);
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
