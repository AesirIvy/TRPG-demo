#include <cstdlib>
#include <iostream>
#include <sstream>

#include "being.hxx"
#include "util.hxx"

static std::vector<Being *> s_allyParty;
static std::vector<Being *> s_enemyParty;

std::vector<Being *> *checkSide(const std::string &side) {
	if (side == "ally" || side == "1") return &s_allyParty;
	if (side == "enemy" || side == "2") return &s_enemyParty;
	std::cout << "invalid argument: must be ally or enemy, but got ";
	std::cout << side << '\n' << std::endl;
	return nullptr;
}

void list(const std::vector<std::string> &args) {
	if (args.size() < 2) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	system("clear");
	if (args[1] == "artifact" || args[1] == "1") {
		printCSV("src/data/equipment/artifact.csv");
	} else if (args[1] == "creature" || args[1] == "2") {
		printCSV("src/data/being/creature.csv");
	} else if (args[1] == "character" || args[1] == "3") {
		printCSV("src/data/being/character.csv");
	} else if (args[1] == "machine" || args[1] == "4") {
		printCSV("src/data/being/machine.csv");
	} else if (args[1] == "weapon" || args[1] == "5") {
		printCSV("src/data/equipment/weapon.csv");
	} else {
		std::cout << "no valid argument\n" << std::endl;
	}
}

void view(const std::vector<std::string> &args) {
	if (args.size() < 2) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	const std::vector<Being *> *party = checkSide(args[1]);
	if (party) printParty(*party);
}

void add(const std::vector<std::string> &args) {
	if (args.size() < 4) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	std::vector<Being *> *party = checkSide(args[1]);
	if (!party) return;
	if (args[2] == "creature" || args[2] == "1") {
		try {
			(*party).push_back(new Creature(args[3]));
		} catch (const std::invalid_argument &error) {
			std::cout << "invalid id\n" << std::endl;
		}
		printParty(*party);
	} else if (args[2] == "character" || args[2] == "2") {
		try {
			(*party).push_back(new Character(args[3]));
		} catch (const std::invalid_argument &error) {
			std::cout << "invalid id\n" << std::endl;
		}
		printParty(*party);
	} else {
		std::cout << "invalid argument\n" << std::endl;
	}
}

void remove(const std::vector<std::string> &args) {
	if (args.size() < 3) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	std::vector<Being *> *party = checkSide(args[1]);
	if (!party) return;
	int index = std::stoi(args[2]);
	if (index >= (*party).size()) {
		std::cout << "invalid index\n" << std::endl;
		return;
	}
	(*party).erase((*party).begin() + index);
	printParty(*party);
}

void equip(const std::vector<std::string> &args) {
	if (args.size() < 5) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	const std::vector<Being *> *party = checkSide(args[1]);
	if (!party) return;
	int index = std::stoi(args[2]);
	if (index >= (*party).size()) {
		std::cout << "invalid index\n" << std::endl;
		return;
	}
	Character *character;
	if (!(character = dynamic_cast<Character *>((*party)[index]))) {
		std::cout << "only character can equip equipment\n" << std::endl;
		return;
	}
	if (args[3] == "artifact" || args[3] == "1") {
		try {
			(*character).equip(Artifact(args[4]));
		} catch (const std::invalid_argument &error) {
			std::cout << "invalid id\n" << std::endl;
		}
		printParty(*party);
	} else if (args[3] == "weapon" || args[3] == "2") {
		try {
			(*character).equip(Weapon(args[4]));
		} catch (const std::invalid_argument &error) {
			std::cout << "invalid id\n" << std::endl;
		}
		printParty(*party);
	} else {
		std::cout << "invalid argument: must be artifact or weapon, but got ";
		std::cout << args[3] << '\n' << std::endl;
	}
}

void battle();

void simulation() {
	std::string ui;  // user input
	std::vector<std::string> args;
	system("clear");
	std::cout << "digit can be use for shorthand, ex: 1 1 for list creature\n" << std::endl;
	while (true) {
		std::cout << "1: list <artifact|creature|character|machine|weapon>\n";
		std::cout << "2: view <ally|enemy>\n";
		std::cout << "3: add <ally|enemy> <creature|character> <id>\n";
		std::cout << "4: remove <ally|enemy> <index>\n";
		std::cout << "5: equip <ally|enemy> <index> <artifact|weapon> <id>\n";
		std::cout << "6\n";
		std::cout << "7\n";
		std::cout << "8\n";
		std::cout << "9\n";
		std::cout << "0: quit\n" << std::endl;

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

		if (args[0] == "list" || args[0] == "1") list(args);
		else if (args[0] == "view" || args[0] == "2") view(args);
		else if (args[0] == "add" || args[0] == "3") add(args);
		else if (args[0] == "remove" || args[0] == "4") remove(args);
		else if (args[0] == "equip" || args[0] == "5") equip(args);
		else if (args[0] == "quit" || args[0] == "0") {system("clear"); return;}
		else std::cout << "no valid command\n" << std::endl;
	}
}
