#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>

namespace Utils {

	bool checkCollision(const sf::RectangleShape&, const sf::RectangleShape&);

	sf::RectangleShape getRectangleAt(sf::Vector2f location, sf::Color);

	int getRandomInt(int min, int max);

};

#endif
