#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "being.hxx"

void printCSV(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	std::string temp;

	unsigned short column;
	unsigned short lastColIdx;  // last column index

	std::getline(file, line);
	std::istringstream stream(line);
	lastColIdx = std::count_if(line.begin(), line.end(), [](char c){return c == '\t';});

	std::cout << "╔";
	for (int i = 0; i < 16; ++i) std::cout << "═";
	for (int i = 0; i < lastColIdx; ++i) {
		std::cout << "╤";
		for (int j = 0; j < 8; ++j) {
			std::cout << "═";
		}
	}
	std::cout << "╗\n";

	column = 0;
	std::cout << "║";
	while(stream >> temp) {
		std::cout << temp;
		for (unsigned short i = temp.size(); i < 16; ++i) {
			if (i == 8 && column > 0) break;
			std::cout << ' ';
		}
		if (column != lastColIdx) std::cout << "│";
		++column;
	}
	std::cout << "║\n";
	std::cout << "╠";
	for (int i = 0; i < 16; ++i) std::cout << "═";
	for (int i = 0; i < lastColIdx; ++i) {
		std::cout << "╪";
		for (int j = 0; j < 8; ++j) {
			std::cout << "═";
		}
	}
	std::cout << "╣\n";

	while (std::getline(file, line)) {
		std::istringstream stream(line);
		column = 0;
		std::cout << "║";
		while(stream >> temp) {
			std::cout << temp;
			for (unsigned short i = temp.size(); i < 16; ++i) {
				if (i == 8 && column > 0) break;
				std::cout << ' ';
			}
			if (column != lastColIdx) std::cout << "│";
			++column;
		}
		std::cout << "║\n";
		if (file.peek() == EOF) break;
		std::cout << "╟";
		for (int i = 0; i < 16; ++i) std::cout << "─";
		for (int i = 0; i < lastColIdx; ++i) {
			std::cout << "┼";
			for (int j = 0; j < 8; ++j) {
				std::cout << "─";
			}
		}
		std::cout << "╢\n";
	}

	std::cout << "╚";
	for (int i = 0; i < 16; ++i) std::cout << "═";
	for (int i = 0; i < lastColIdx; ++i) {
		std::cout << "╧";
		for (int j = 0; j < 8; ++j) {
			std::cout << "═";
		}
	}
	std::cout << "╝\n";

	file.close();
	std::cout << std::endl;
}

void printParty(const std::vector<Being *> &party) {
	if (party.empty()) {
		std::cout << "party is empty\n" << std::endl;
		return;
	}
	for (unsigned short i = 0; i < party.size(); ++i) {
		std::cout << party[i]->id;
		if (Character *character = dynamic_cast<Character *>(party[i])) {
			std::cout << " weapon: ";
			std::cout << character->weapon.name << " artifact: ";
			std::cout << character->artifact.name;
		}
		std::cout << '\n';
		std::cout << "HP: " << party[i]->current.HP << '/' << party[i]->maxHP << '\n';
		std::cout << "ATK: " << party[i]->current.ATK << '\n';
		std::cout << "DEF: " << party[i]->current.DEF << '\n';
		std::cout << "TD: " << party[i]->current.TD << '\n';
		std::cout << '\n';
	}
	std::cout << std::endl;
}
