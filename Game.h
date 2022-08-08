#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include "TextureManager.h"

#define BOX_SIZE 20 

class Game {
public:
	Game();
	~Game();

	void init();
	void GenerateRandomFood();
	void DrawSpawnedFood();
	void Reset();
	void GameLoop();
	TextureManager texManager;
private:
	std::vector<Food> spawnedFood;
	sf::RenderWindow* screen;
	Snake* player;
};

#endif
