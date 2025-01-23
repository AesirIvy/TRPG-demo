#include <initializer_list>

#include <vector>

#include "battle.hxx"
#include "being.hxx"

void addToTimeline(std::vector<Being *> &timeline, Being &being) {
	being.IP = 100 - being.current.SPD;
	for (unsigned short i = 0; i < timeline.size(); ++i) {
		if (being.IP < timeline[i]->IP) {
			timeline.insert(timeline.begin() + i, &being);
			return;
		}
	}
	timeline.push_back(&being);
}

void startBattle(std::vector<Being *> allyArr, std::vector<Being *> enemyArr) {
	std::vector<Being *> timeline;
	for (auto arr: {allyArr, enemyArr}) {
		for (unsigned short i = 0; i < arr.size(); ++i) {
			addToTimeline(timeline, *arr[i]);
		}
	}
}
