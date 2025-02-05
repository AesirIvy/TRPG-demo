#include <array>

#include "being.hxx"

void addToTimeline(std::vector<Being *> &timeline, Being &being) {
	being.IP = being.current.TD;
	for (unsigned short i = 0; i < timeline.size(); ++i) {
		if (being.IP < timeline[i]->IP) {
			timeline.insert(timeline.begin() + i, &being);
			return;
		}
	}
	timeline.push_back(&being);
}

void resolveStatus(Being &being) {
	for (const Status &status: being.statusVec) {
		if (status.isDamage) being.receiveDmg(status.amount);
		else if (status.isLeak) being.AP -= status.amount;
		else if (status.isSlow) being.current.SP -= status.amount;
	}
}

Being *advanceTimeline(std::vector<Being *> &timeline) {
	Being *leadBeing = timeline[0];
	timeline.erase(timeline.begin());
	for (unsigned short i = 0; i < timeline.size(); ++i) {
		timeline[i]->IP -= leadBeing->IP;
	}
	return leadBeing;
}

void console_wars(const std::vector<Being *> &allyVec, const std::vector<Being *> &enemyVec) {
	std::vector<Being *> timeline;
	for (const std::vector<Being *> &vec: {allyVec, enemyVec}) {
		for (unsigned short i = 0; i < vec.size(); ++i) {
			addToTimeline(timeline, *vec[i]);
		}
	}

	while (true) {
		if (allyVec.empty()) {
			std::cout << "They won this fight." << std::endl;
			return;
		}
		if (enemyVec.empty()) {
			std::cout << "You won this fight." << std::endl;
			return;
		}

		Being *leadBeing = advanceTimeline(timeline);
		resolveStatus(*leadBeing);
		if (dynamic_cast<Character *>(leadBeing)) {
			// do stuff
		} else {
			// let it resolve
		}
	}
}
