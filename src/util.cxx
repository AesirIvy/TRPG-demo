#include <fstream>
#include <iostream>
#include <sstream>

#include "util.hxx"

void printRow(const std::vector<uint8_t> &colWidth, std::string &line) {
	std::string token;
	std::istringstream stream(line);
	std::cout << "║";
	for (uint8_t column = 0; column < colWidth.size(); ++column) {
		stream >> token;
		std::cout << token;
		for (uint8_t i = token.size(); i < colWidth[column]; ++i) {
			std::cout << ' ';
		}
		if (column != colWidth.size() - 1) std::cout << "│";
	}
	std::cout << "║\n";
}

void printRowSep(
	const std::vector<uint8_t> &colWidth,
	const std::string &op,
	const std::string &base,
	const std::string &sep,
	const std::string &end
) {
	std::cout << op;
	for (uint8_t column = 0; column < colWidth.size(); ++column) {
		for (uint8_t i = 0; i < colWidth[column]; ++i) std::cout << base;
		if (column != colWidth.size() - 1) std::cout << sep;
	}
	std::cout << end << '\n';
}

void printCSV(std::string filePath) {
	std::ifstream file(filePath);
	std::string line;
	std::string token;

	std::vector<uint8_t> colWidth;

	std::getline(file, line);
	std::istringstream stream(line);
	uint8_t count = 0;
	while (std::getline(stream, token, '\t')) {
		if (count < 2) colWidth.push_back(16);
		else colWidth.push_back(8);
		++count;
	}

	printRowSep(colWidth, "╔", "═", "╤", "╗");
	printRow(colWidth, line);
	printRowSep(colWidth, "╠", "═", "╪", "╣");

	while (std::getline(file, line)) {
		printRow(colWidth, line);
		if (file.peek() == EOF) break;
		printRowSep(colWidth, "╟", "─", "┼", "╢");
	}

	printRowSep(colWidth, "╚", "═", "╧", "╝");

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
			std::cout << "\tweapon: ";
			std::cout << character->weapon.name << " artifact: ";
			std::cout << character->artifact.name;
		}
		std::cout << '\n';
		std::cout << "HP: " << party[i]->current.HP << '/' << party[i]->maxHP << ' ';
		std::cout << "ATK: " << party[i]->current.ATK << ' ';
		std::cout << "DEF: " << party[i]->current.DEF << ' ';
		std::cout << "TD: " << party[i]->current.TD << '\n';
		std::cout << '\n';
	}
	std::cout << std::endl;
}
