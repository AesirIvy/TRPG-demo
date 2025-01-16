#include <SFML/Graphics.hpp>

int main() {
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
	return 0;
}
