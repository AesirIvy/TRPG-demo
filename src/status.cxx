#include <fstream>

#include "being.hxx"
#include "status.hxx"

int readIntFromFile(std::ifstream &file) {
	std::string line;
	std::getline(file, line);
	size_t pos = line.find('\t');
	if (pos == std::string::npos) throw std::out_of_range("missing a tab in " + line);
	return std::stoi(line.substr(pos + 1));
}

Status::Status(std::string name, uint8_t stack): name(name), stack(stack) {
	std::ifstream file("src/data/status/" + name + ".txt");
	try {
		amount = readIntFromFile(file);
		isDamage = readIntFromFile(file);
		isLeak = readIntFromFile(file);
	}  catch (const std::out_of_range &error) {
		std::cerr << error.what() << '\n';
		std::cerr << "error parsing the file src/data/status/" << name << ".txt" << std::endl;
	}
}

void StatusManager::addStatus(const Status &status) {
	statusVec.push_back(status);
}

void StatusManager::resolveStatus(Being &being) {
	for (const Status &status: statusVec) {
		if (status.isDamage) being.receiveDmg(status.amount);
		else if (status.isLeak) being.AP -= status.amount;
	}
}
