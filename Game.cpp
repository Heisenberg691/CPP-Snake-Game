#include "Game.h"
#include "Utils.h"
#include <iostream>

Game::Game()
{
    this->player = nullptr;
    this->screen = nullptr;
    this->player = nullptr;
 
}

Game::~Game()
{
   
}

void Game::GameLoop()
{

    sf::Context context;
    sf::Clock deltaT;
    sf::Clock deltaTFood;
    player->SetMoving(true);

    while (this->screen->isOpen())
    {

        sf::Event event;
        while (this->screen->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                this->screen->close();
                break;
            case sf::Event::KeyReleased:

                switch (event.key.code)
                {
                    case sf::Keyboard::W:
                        if (player->CanGotoDirection(DIRECTION::UP)) {
                            player->SetDirection(DIRECTION::UP);
                        }
                        break;
                    case sf::Keyboard::A:
                        if (player->CanGotoDirection(DIRECTION::LEFT)) {
                            player->SetDirection(DIRECTION::LEFT);
                        }
                        break;
                    case sf::Keyboard::S:
                        if (player->CanGotoDirection(DIRECTION::DOWN)) {
                            player->SetDirection(DIRECTION::DOWN);
                        }
                        break;
                    case sf::Keyboard::D:
                        if (player->CanGotoDirection(DIRECTION::RIGHT)) {
                            player->SetDirection(DIRECTION::RIGHT);
                        }
                        break;
                }

                break;
            }
        }

        this->screen->clear();
        player->Draw();
        Game::DrawSpawnedFood();
        this->screen->display();
        this->screen->setFramerateLimit(60);
        sf::Int32 DeltaTElapsedTime = deltaT.getElapsedTime().asMilliseconds();
        sf::Int32 FoodDeltaTElapsedTime = deltaTFood.getElapsedTime().asMilliseconds();

        if (DeltaTElapsedTime > 200) {
            player->Move();
            deltaT.restart();

            
            for (unsigned int i = 0; i < spawnedFood.size(); i++) {
                if (Utils::checkCollision(player->GetBodyPartByIndex(0), spawnedFood[i].shape)) {
                    player->EatFood(spawnedFood[i].bodyParts);
                    spawnedFood.erase(spawnedFood.begin() + i);
                    break;
                }
            }

        }
        if (FoodDeltaTElapsedTime > 1500) {
            deltaTFood.restart();
            if (Utils::getRandomInt(0, 1) == 1) {
                std::cout << "Spawned food" << std::endl;
                Game::GenerateRandomFood();
            }
        }
        if (player->IsSnakeDead()) {
            Game::Reset();
        }
       

    }
}


void Game::init()
{
    this->screen = new sf::RenderWindow(sf::VideoMode(800, 800), "Snake Game");
    texManager.loadTexture("food_1", "Sprites/fruit.png");
    this->player = new Snake(this->screen, 5, 20.0);
    GameLoop();
}

void Game::GenerateRandomFood()
{
    int foodType = Utils::getRandomInt(0, 0);
    Food newFood;

    switch (foodType) {
        case 0:
            sf::Vector2f foodShapeSize(22.0, 22.0);
            newFood = Food(this->screen, texManager.getTexture("food_1"), 1, foodShapeSize);
            spawnedFood.push_back(newFood);
        break;
    }

}

void Game::DrawSpawnedFood()
{
    for (unsigned int i = 0; i < spawnedFood.size(); i++) {
        this->screen->draw(spawnedFood[i].shape);
    }
}

void Game::Reset()
{
    this->player->Respawn();
    spawnedFood.clear();
}




