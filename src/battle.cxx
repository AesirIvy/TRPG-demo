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

	while (!allyVec.empty() && !enemyVec.empty()) {
		Being *leadBeing = advanceTimeline(timeline);
		if (dynamic_cast<Character *>(leadBeing)) {
			// do stuff
		} else {
			// let it resolve
		}
	}
}
