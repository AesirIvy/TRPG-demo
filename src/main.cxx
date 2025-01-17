#include <SFML/Graphics.hpp>

#include "being.hxx"

int main() {
	sf::RenderWindow window(sf::VideoMode({960, 544}), "TRPG-demo");
	window.setVerticalSyncEnabled(true);

	//test
	Creature megaAraney = Creature("megaAraney");
	Character fenris = Character("Fenris");

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear();
		window.display();
	}
	return 0;
}
