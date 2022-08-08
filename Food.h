#ifndef FOOD_H
#define FOOD_H
#include <SFML/Graphics.hpp>

class Food {
public:
	Food();
	Food(sf::RenderWindow* screen, sf::Texture* texture, int bodyParts, sf::Vector2f size);
	~Food();

	sf::RectangleShape shape;
	int bodyParts;
private:
	sf::Vector2f size;
	sf::RenderWindow* screen;

};

#endif
