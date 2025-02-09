#include <array>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <unordered_map>

#include "battle.hxx"
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
	static const std::string fileArr[5] = {
		"src/data/equipment/artifact.csv",
		"src/data/being/character.csv",
		"src/data/being/creature.csv",
		"src/data/being/machine.csv",
		"src/data/equipment/weapon.csv"
	};
	static const std::unordered_map<std::string, std::string> fileMap {
		{"artifact", fileArr[0]}, {"1", fileArr[0]},
		{"character", fileArr[1]}, {"2", fileArr[1]},
		{"creature", fileArr[2]}, {"3", fileArr[2]},
		{"machine", fileArr[3]}, {"4", fileArr[3]},
		{"weapon", fileArr[4]}, {"5", fileArr[4]}
	};
	auto iter = fileMap.find(args[1]);
	if (iter != fileMap.end()) printCSV(iter->second);
	else std::cout << "no valid argument\n" << std::endl;
}

void viewParty(const std::vector<std::string> &args) {
	if (args.size() < 2) {
		std::cout << "missing argument\n" << std::endl;
		return;
	}
	const std::vector<Being *> *party = checkSide(args[1]);
	if (party) printParty(*party);
}

void addBeingToParty(const std::vector<std::string> &args) {
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
			std::cout << error.what() << '\n' << std::endl;
		}
		printParty(*party);
	} else if (args[2] == "character" || args[2] == "2") {
		try {
			(*party).push_back(new Character(args[3]));
		} catch (const std::invalid_argument &error) {
			std::cout << error.what() << '\n' << std::endl;
		}
		printParty(*party);
	} else {
		std::cout << "invalid argument\n" << std::endl;
	}
}

void removeBeingFromParty(const std::vector<std::string> &args) {
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

void equipBeing(const std::vector<std::string> &args) {
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
			std::cout << error.what() + '\n' << std::endl;
		}
		printParty(*party);
	} else if (args[3] == "weapon" || args[3] == "2") {
		try {
			(*character).equip(Weapon(args[4]));
		} catch (const std::invalid_argument &error) {
			std::cout << error.what() + '\n' << std::endl;
		}
		printParty(*party);
	} else {
		std::cout << "invalid argument: must be artifact or weapon, but got ";
		std::cout << args[3] << '\n' << std::endl;
	}
}

void battle(const std::vector<std::string> &args) {
	console_war(s_allyParty, s_enemyParty);
}

void quit(const std::vector<std::string> &args) {
	system("clear");
	exit(0);
}

void simulation() {
	std::string ui;  // user input
	std::vector<std::string> args;

	static const std::unordered_map<
		std::string, std::function<void(const std::vector<std::string> &)>
		> commandMap = {
		{"list", list}, {"1", list},
		{"view", viewParty}, {"2", viewParty},
		{"add", addBeingToParty}, {"3", addBeingToParty},
		{"remove", removeBeingFromParty}, {"4", removeBeingFromParty},
		{"equip", equipBeing}, {"5", equipBeing},
		{"battle", battle}, {"7", battle},
		{"quit", quit}, {"0", quit}
	};

	system("clear");
	std::cout << "digit can be used as shorthand, ex: 1 2 for list character\n" << std::endl;
	while (true) {
		std::cout <<
			"1: list <artifact|character|creature|machine|weapon>\n"
			"2: view <ally|enemy>\n"
			"3: add <ally|enemy> <creature|character> <id>\n"
			"4: remove <ally|enemy> <index>\n"
			"5: equip <ally|enemy> <index> <artifact|weapon> <id>\n"
			"6\n"
			"7: battle\n"
			"8\n"
			"9\n"
			"0: quit\n\n"
			">>> ";

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

		auto iter = commandMap.find(args[0]);
		if (iter != commandMap.end()) {
			iter->second(args);
		} else {
			std::cout << "no valid command\n" << std::endl;
		}
	}
}
