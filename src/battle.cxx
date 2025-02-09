#include <algorithm>
#include <utility>

#include "being.hxx"

void resolveStatus(Being &being) {
	for (const Status &status: being.statusVec) {
		if (status.isDamage) being.receiveDmg(status.amount);
		else if (status.isLeak) being.AP -= status.amount;
		else if (status.isSlow) being.current.SP -= status.amount;
	}
}

std::pair<bool, Being *> advanceTimeline(
	std::vector<Being *> &allyParty,
	std::vector<Being *> &enemyParty
) {
	bool isAlly;
	Being *leadBeing;

	// ls: left side
	// rs: right side
	auto minBeingIP = [](const Being *lsBeing, const Being *rsBeing) {
		return lsBeing->IP < rsBeing->IP;
	};
	Being *allyLeadBeing = *std::min_element(allyParty.begin(), allyParty.end(), minBeingIP);
	Being *enemyLeadBeing = *std::min_element(enemyParty.begin(), enemyParty.end(), minBeingIP);
	if (allyLeadBeing->IP < enemyLeadBeing->IP) {
		isAlly = true;
		leadBeing = allyLeadBeing;
	}
	else {
		isAlly = false;
		leadBeing = enemyLeadBeing;
	}

	for (uint8_t i = 0; i < allyParty.size(); ++i) {
		allyParty[i]->IP -= leadBeing->IP;
	}
	for (uint8_t i = 0; i < enemyParty.size(); ++i) {
		allyParty[i]->IP -= leadBeing->IP;
	}
	return std::make_pair(isAlly, leadBeing);
}

void console_war(std::vector<Being *> &allyParty, std::vector<Being *> &enemyParty) {
	while (true) {
		if (allyParty.empty()) {
			std::cout << "They won this fight." << std::endl;
			return;
		}
		if (enemyParty.empty()) {
			std::cout << "You won this fight." << std::endl;
			return;
		}

		bool isAlly;
		Being *leadBeing;
		std::tie(isAlly, leadBeing) = advanceTimeline(allyParty, enemyParty);
		resolveStatus(*leadBeing);
		if (isAlly) {
			leadBeing->passive(0, *leadBeing, allyParty, enemyParty);
			if (dynamic_cast<Character *>(leadBeing)) {
				std::cout << "Q: " << leadBeing->qSkillName << "\n"
					"W: " << leadBeing->wSkillName << "\n"
					"E: " << leadBeing->eSkillName << "\n"
					"R: " << leadBeing->rSkillName << '\n';
				if (leadBeing->position < 4) std::cout << "T: switch to rearguard";
				else std::cout << "T: switch to vanguard";
				std::cout << "G: guard\n";
				std::cout << ">>> ";
			} else {
				break;  // let it resolve
			}
		} else {
			leadBeing->passive(0, *leadBeing, enemyParty, allyParty);
			// let it resolve
		}
	}
}
