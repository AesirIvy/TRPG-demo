#include <iostream>

#include <SFML/Graphics.hpp>

#include "being.hxx"

int main() {
	sf::RenderWindow window(sf::VideoMode({960, 544}), "TRPG-demo");
	window.setVerticalSyncEnabled(true);

	//test
	Creature megarana = Creature("Megarana");
	Character fenris = Character("Fenris");
	std::cout << fenris.current.ATK << '\n';
	fenris.equipWeapon("Aetherbane");
	std::cout << fenris.current.ATK << "\n\n";
	std::cout << megarana.current.HP << '\n';
	fenris.basicAttack(megarana);
	std::cout << megarana.current.HP << std::endl;

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
