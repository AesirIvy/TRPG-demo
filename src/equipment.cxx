#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "equipment.hxx"

Equipment::Equipment(std::string name): name(name) {
	std::memset(&increment, 0, sizeof(increment));
}

void Equipment::statInitFromFile(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	while (std::getline(file, line)) {
		bool nextLoop = false;
		std::string token;
		std::stringstream ss(line);

		std::getline(ss, token, '\t');
		if (token != name) continue;

		std::getline(ss, token, '\t');
		increment.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.DEF = std::stoi(token);

		return;
	}
	std::cout << name << " not found in database" << std::endl;
}

Artifact::Artifact(std::string name): Equipment(name) {
	statInitFromFile("src/data/equipment/artifact.csv");
}

Weapon::Weapon(std::string name): Equipment(name) {
	statInitFromFile("src/data/equipment/weapon.csv");
}
