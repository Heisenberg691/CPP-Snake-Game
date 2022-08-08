#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>

enum DIRECTION { UP=0, RIGHT, DOWN, LEFT};

class Snake {
public:
	Snake();
	Snake(sf::RenderWindow* screen,int bodyParts, double partSize);
	~Snake();

	void Draw();
	void SetMoving(bool moving);
	void Move();
	bool IsSnakeDead();
	void SetDirection(DIRECTION dir);
	bool CanGotoDirection(DIRECTION dir);
	void EatFood(int bodyParts);
	void Respawn();
	sf::RectangleShape& GetBodyPartByIndex(int index);
private:
	std::vector<sf::RectangleShape> tail;
	DIRECTION dir;
	bool isMoving;
	int movementScale;
	sf::RenderWindow* screen;
	double partSize;
	int partsQueue;
	int defaultBodyParts;
	

};

#endif
