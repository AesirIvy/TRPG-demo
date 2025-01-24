#include <array>
#include <iostream>
#include <vector>

// #include <SFML/Graphics.hpp>

#include "battle.hxx"
#include "being.hxx"
#include "simulation.hxx"

int main() {
	simulation();

/*
	sf::RenderWindow window(sf::VideoMode({960, 544}), "TRPG-demo");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear();
		window.display();
	}
*/
	return 0;
}
