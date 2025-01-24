#include <cstdlib>
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
	const unsigned short lastColIdx = 4;

	std::cout << "╔";
	for (int i = 0; i < 16; ++i) std::cout << "═";
	for (int i = 0; i < lastColIdx; ++i) {
		std::cout << "╤";
		for (int j = 0; j < 8; ++j) {
			std::cout << "═";
		}
	}
	std::cout << "╗\n";

	std::getline(file, line);
	std::cout << "║";
	std::istringstream stream(line);
	int column = 0;
	while(stream >> temp) {
		std::cout << temp;
		for (unsigned short i = temp.size(); i < 16; ++i) {
			if (i == 8 & column > 0) break;
			std::cout << ' ';
		}
		if (column != lastColIdx) std::cout << "│";
		++column;
	}
	std::cout << "║\n";
	std::cout << "╠";
	for (int i = 0; i < 16; ++i) std::cout << "═";
	for (int i = 0; i < 4; ++i) {
		std::cout << "╪";
		for (int j = 0; j < 8; ++j) {
			std::cout << "═";
		}
	}
	std::cout << "╣\n";

	while (std::getline(file, line)) {
		std::cout << "║";
		std::istringstream stream(line);
		int column = 0;
		while(stream >> temp) {
			std::cout << temp;
			for (unsigned short i = temp.size(); i < 16; ++i) {
				if (i == 8 & column > 0) break;
				std::cout << ' ';
			}
			if (column != lastColIdx) std::cout << "│";
			++column;
		}
		std::cout << "║\n";
		if (file.peek() == EOF) break;
		std::cout << "╟";
		for (int i = 0; i < 16; ++i) std::cout << "─";
		for (int i = 0; i < 4; ++i) {
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

void printParty(std::vector<Being *> &party) {
	if (party.empty()) {
		std::cout << "party is empty\n" << std::endl;
		return;
	}
	for (unsigned short i = 0; i < party.size(); ++i) {
		std::cout << party[i]->name;
		if (Character *character = dynamic_cast<Character *>(party[i])) {
			std::cout << " weapon: ";
			std::cout << character->weapon.name << " artifact: ";
			std::cout << character->artifact.name;
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}

void simulation() {
	std::string ui;
	std::vector<std::string> args;
	std::vector<Being *> allyParty;
	std::vector<Being *> enemyParty;
	system("clear");
	std::cout << "digit can be use for shorthand, ex: 1 1 for list creature\n" << std::endl;
	while (true) {
		std::cout << "list <creature|character>\n";
		std::cout << "view <ally|enemy>\n";
		std::cout << "add <ally|enemy> <creature|character> <name>\n";
		std::cout << "remove <ally|enemy> <index>\n";
		std::cout << "5\n";
		std::cout << "6\n";
		std::cout << "7\n";
		std::cout << "8\n";
		std::cout << "9\n";
		std::cout << "quit\n" << std::endl;

		std::cout << ">>> ";
		args.clear();
		std::getline(std::cin, ui);
		std::istringstream stream(ui);
		std::string temp;
		while(stream >> temp) {
			args.push_back(temp);
		}

		if (args.empty()) {
			std::cout << "no command entered\n" << std::endl;
			continue;
		}
		if (args[0] == "list" || args[0] == "1") {
			if (args.size() < 2) {
				std::cout << "missing argument\n" << std::endl;
				continue;
			}
			system("clear");
			if (args[1] == "creature" || args[1] == "1") {
				printCSV("src/data/being/creature.csv");
			} else if (args[1] == "character" || args[1] == "2") {
				printCSV("src/data/being/character.csv");
			} else {
				std::cout << "no valid argument\n" << std::endl;
			}
			continue;
		}
		if (args[0] == "view" || args[0] == "2") {
			if (args.size() < 2) {
				std::cout << "missing argument\n" << std::endl;
				continue;
			}
			if (args[1] == "ally" || args[1] == "1") {
				printParty(allyParty);
			} else if (args[1] == "enemy" || args[1] == "2") {
				printParty(enemyParty);
			} else {
				std::cout << "invalid argument: must be ally or enemy, but got ";
				std::cout << args[1] << '\n' << std::endl;
			}
			continue;
		}
		if (args[0] == "add" || args[0] == "3") {
			if (args.size() < 4) {
				std::cout << "missing argument\n" << std::endl;
				continue;
			}
			std::vector<Being *> *party;
			if (args[1] == "ally" || args[1] == "1") party = &allyParty;
			else if (args[1] == "enemy" || args[1] == "2") party = &enemyParty;
			else {
				std::cout << "invalid argument: must be ally or enemy, but got ";
				std::cout << args[1] << '\n' << std::endl;
				continue;
			}
			if (args[2] == "creature" || args[2] == "1") {
				try {
					(*party).push_back(new Creature(args[3]));
				} catch (const std::invalid_argument &error) {
					std::cout << "invalid name\n" << std::endl;
				}
				printParty(*party);
			} else if (args[2] == "character" || args[2] == "2") {
				try {
					(*party).push_back(new Character(args[3]));
				} catch (const std::invalid_argument &error) {
					std::cout << "invalid name\n" << std::endl;
				}
				printParty(*party);
			} else {
				std::cout << "invalid argument\n" << std::endl;
			}
			continue;
		}
		if (args[0] == "remove" || args[0] == "4") {
			if (args.size() < 3) {
				std::cout << "missing argument\n" << std::endl;
				continue;
			}
			std::vector<Being *> *party;
			if (args[1] == "ally" || args[1] == "1") party = &allyParty;
			else if (args[1] == "enemy" || args[1] == "2") party = &enemyParty;
			else {
				std::cout << "invalid argument: must be ally or enemy, but got ";
				std::cout << args[1] << '\n' << std::endl;
				continue;
			}
			int index = std::stoi(args[2]);
			if (index >= (*party).size()) {
				std::cout << "invalid index\n" << std::endl;
				continue;
			}
			(*party).erase((*party).begin() + index);
			printParty((*party));
			continue;
		}
		if (args[0] == "quit" || args[0] == "0") {
			system("clear");
			return;
		}
		std::cout << "no valid command\n" << std::endl;
		continue;
	}
}
