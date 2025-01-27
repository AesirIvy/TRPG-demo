#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "equipment.hxx"

Equipment::Equipment(const std::string &id): id(id) {
	std::memset(&increment, 0, sizeof(increment));
}

void Equipment::statInitFromFile(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	while (std::getline(file, line)) {
		std::string token;
		std::stringstream ss(line);

		std::getline(ss, token, '\t');
		if (token != id) continue;

		std::getline(ss, token, '\t');
		name = token;
		std::getline(ss, token, '\t');
		increment.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.DEF = std::stoi(token);

		return;
	}
	std::cout << id << " not found in database" << std::endl;
}

Artifact::Artifact(const std::string &id): Equipment(id) {
	statInitFromFile("src/data/equipment/artifact.csv");
}

Weapon::Weapon(const std::string &id): Equipment(id) {
	statInitFromFile("src/data/equipment/weapon.csv");
}
