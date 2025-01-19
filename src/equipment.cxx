#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "equipment.hxx"

Equipment::Equipment(std::string name): m_name(name), increment() {

}

void Equipment::statInitFromFile(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	while (std::getline(file, line)) {
		bool nextLoop = false;
		std::string token;
		std::stringstream ss(line);

		std::getline(ss, token, '\t');
		if (token != m_name) {
			continue;
		}

		std::getline(ss, token, '\t');
		increment.HP = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.ATK = std::stoi(token);
		std::getline(ss, token, '\t');
		increment.DEF = std::stoi(token);

		return;
	}
	std::cout << m_name << " not found in database" << std::endl;
}

Weapon::Weapon(std::string name): Equipment(name) {
	statInitFromFile("src/data/equipment/weapon.csv");
}
