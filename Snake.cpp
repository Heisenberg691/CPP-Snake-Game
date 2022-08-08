#include "Snake.h"
#include "Utils.h"
#include <iostream>
#include <list>

Snake::Snake()
{
	dir = DIRECTION::UP;
	double x = Utils::getRandomInt(0, screen->getSize().x - 4);
	double y = Utils::getRandomInt(0, screen->getSize().y - 4);
	sf::Vector2f position(x, y);
	partSize = 20;
	screen = nullptr;
	movementScale = 5;
	isMoving = false;
	defaultBodyParts = 3;
	partsQueue = 0;
}

Snake::Snake(sf::RenderWindow* screen,int bodyParts,double partSize)
{
	dir = DIRECTION::UP;
	double x = Utils::getRandomInt(0, screen->getSize().x - 4);
	double y = Utils::getRandomInt(0, screen->getSize().y - 4);
	sf::Vector2f position(x, y);

	this->partSize = partSize;
	this->screen = screen;
	movementScale = 5;
	partsQueue = 0;
	defaultBodyParts = bodyParts;
	isMoving = false;
	for (int i = 0; i < bodyParts; i++) {
		sf::Color partColor = sf::Color::Cyan;

		if (i!=0) {
			position.y= position.y+ partSize+1;
			partColor = sf::Color::Green;
		
		}
		sf::Vector2f size(partSize, partSize);
		sf::RectangleShape newBodyPart(size);
		newBodyPart.move(position);
		newBodyPart.setFillColor(partColor);
		tail.push_back(newBodyPart);
	}
}

Snake::~Snake()
{
}

sf::Vector2f GET_VECTOR2_FROM_DIRECTION(DIRECTION dir)
{
	if (dir == DOWN)
	{
		return sf::Vector2f(0, 1);
	}

	if (dir == UP)
	{
		return sf::Vector2f(0, -1);
	}

	if (dir == LEFT)
	{
		return sf::Vector2f(-1, 0);
	}

	if (dir == RIGHT)
	{
		return sf::Vector2f(1, 0);
	}

	return sf::Vector2f(0, 0);
}

void Snake::Draw()
{
	for (unsigned int i = 0; i < tail.size(); i++) {
		screen->draw(tail[i]);
	}
}


void Snake::SetMoving(bool moving)
{
	isMoving = moving;
}

void Snake::Move()
{
	if (!isMoving) {
		return;
	}
	
	sf::Vector2f movement = GET_VECTOR2_FROM_DIRECTION(dir);
	sf::Vector2f newHeadPos = tail[0].getPosition();
	sf::Vector2f lastPartLastPos = tail[tail.size()-1].getPosition();

	// hitting walls check
	int x = tail[0].getGlobalBounds().left, y = tail[0].getGlobalBounds().top;

	if (x <= 0) {
		newHeadPos.x = screen->getSize().x;
	}
	else if (x >= screen->getSize().x) {
		newHeadPos.x = 0;
	}
	else if (y < 0) {
		newHeadPos.y = screen->getSize().y;
	}
	else if (y > screen->getSize().y) {
		newHeadPos.y = 0;
	}

	for (unsigned int i = tail.size()-1; i > 0; i--) {
		tail[i].setPosition(tail[i - 1].getPosition());
	}

	tail[0].setPosition(newHeadPos.x + (movement.x*(partSize+1)), newHeadPos.y+ (movement.y* (partSize + 1)));

	if (partsQueue>0){
		sf::Vector2f position(lastPartLastPos);
		sf::Color partColor = sf::Color::Green;
		sf::Vector2f size(partSize, partSize);
		sf::RectangleShape newBodyPart(size);
		newBodyPart.setPosition(position);
		newBodyPart.setFillColor(partColor);
		tail.push_back(newBodyPart);
		partsQueue--;
	}

}

bool Snake::IsSnakeDead()
{
	for (unsigned int i = 1; i < tail.size(); i++) {
		if (Utils::checkCollision(tail[0], tail[i]))
			return true;
	}
	return false;
}

void Snake::SetDirection(DIRECTION dir)
{
	this->dir = dir;
}

bool Snake::CanGotoDirection(DIRECTION dir)
{
	switch (dir)
	{
	case UP:
		if (this->dir == DIRECTION::DOWN) {
			return false;
		}
		break;
	case RIGHT:
		if (this->dir == DIRECTION::LEFT) {
			return false;
		}
		break;
	case DOWN:
		if (this->dir == DIRECTION::UP) {
			return false;
		}
		break;
	case LEFT:
		if (this->dir == DIRECTION::RIGHT) {
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}

void Snake::EatFood(int bodyParts)
{
	partsQueue = partsQueue + bodyParts;
}

void Snake::Respawn()
{
	dir = DIRECTION::UP;
	partsQueue = 0;
	for (unsigned int i = tail.size() - 1; i >= defaultBodyParts; i--) {
		tail.erase(tail.begin()+i);
	}
	double x = Utils::getRandomInt(0, screen->getSize().x - 4);
	double y = Utils::getRandomInt(0, screen->getSize().y - 4);
	sf::Vector2f position(x, y);
	tail[0].setPosition(position);
	for (int i = 1; i < defaultBodyParts; i++) {
		position.y = position.y + partSize + 1;
		tail[i].setPosition(position);
	}

}

sf::RectangleShape& Snake::GetBodyPartByIndex(int index)
{
	return tail[index];
}

