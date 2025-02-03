#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "equipment.hxx"
#include "util.hxx"

Equipment::Equipment(const std::string &id): id(id) {

}

void Equipment::statInitFromFile(const std::string &filePath) {
	std::istringstream iss = dataFromCSV(filePath, id);
	if (iss.peek() == EOF) throw std::invalid_argument(id + " not found in database\n");

	std::string token;

	std::getline(iss, token, '\t');
	name = token;
	std::getline(iss, token, '\t');
	increment.HP = std::stoi(token);
	std::getline(iss, token, '\t');
	increment.ATK = std::stoi(token);
	std::getline(iss, token, '\t');
	increment.DEF = std::stoi(token);
}

Artifact::Artifact(const std::string &id): Equipment(id) {
	statInitFromFile("src/data/equipment/artifact.csv");
}

Weapon::Weapon(const std::string &id): Equipment(id) {
	statInitFromFile("src/data/equipment/weapon.csv");
}
