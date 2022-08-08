#include "Utils.h"
#include "Game.h"
#include <random>

bool Utils::checkCollision(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

sf::RectangleShape Utils::getRectangleAt(sf::Vector2f location, sf::Color color)
{
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(BOX_SIZE, BOX_SIZE));
	box.setPosition(location);
	box.setFillColor(color);
	return box;
}

int Utils::getRandomInt(int min, int max)
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
	return dist6(rng);
}
