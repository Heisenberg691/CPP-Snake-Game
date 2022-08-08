#include "Food.h"
#include "Utils.h"

Food::Food()
{
	this->bodyParts = 3;
	this->screen = nullptr;

}

Food::Food(sf::RenderWindow* screen, sf::Texture* texture, int bodyParts, sf::Vector2f size)
{
	this->bodyParts = bodyParts;
	this->screen = screen;
	this->size = size;
	shape.setTexture(texture);
	shape.setSize(size);
	double x = Utils::getRandomInt(0, screen->getSize().x - 4);
	double y = Utils::getRandomInt(0, screen->getSize().y - 4);
	sf::Vector2f position(x, y);
	shape.setPosition(position);
}

Food::~Food()
{
}