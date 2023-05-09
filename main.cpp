#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>

#include "entities.hpp"
#include "map.hpp"


// Generate a random number between min and max
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}


// Make COORD
COORD makeCoord(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    return coord;
}

int main() {

    srand(time(0));

    // Initialize player and enemies
    Player player(10, 10);
    std::vector<Entity*> entities;
    entities.push_back(&player);
    for (int i = 0; i < 10; i++) {
        entities.push_back(new Enemy(random(1, MAP_SIZE - 2), random(1, MAP_SIZE - 2)));
    }

    // Generate map
    std::vector<std::vector<char>> map = generateMap();

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD topLeftCorner = makeCoord(0, 0);

    system("cls");

    // Game loop
    while (player.getHealth() > 0) {
        // Clear console

		map = generateMap();

		for (auto entity : entities) {
            map[entity->getX()][entity->getY()] = entity->getSymbol();
        }

        // Set console cusor at top left corner
        SetConsoleCursorPosition(hStdOut, topLeftCorner);

        // Print map
        for (auto row : map) {
            for (auto c : row) {
                std::cout << c << ' ';
            }
            std::cout << std::endl;
        }

        // Print entities
        for (auto entity : entities) {
            std::cout << entity->getSymbol() << ": (" << entity->getX() << ", " << entity->getY() << ") HP: " << entity->getHealth();
            if (entity == &player) {
                std::cout << "Health: " << player.getHealth();
            }
            std::cout << std::endl;
        }

        // Get player input and move the player
        char input;
		input = _getwch();
        if (input == 'w') player.move(-1, 0, entities, map);
        else if (input == 'a') player.move(0, -1, entities, map);
        else if (input == 's') player.move(1, 0, entities, map);
        else if (input == 'd') player.move(0, 1, entities, map);
		else if (input == 27) return 0;
    }

    // Game over
    std::cout << "Game over!" << std::endl;

    // Clean up
    for (auto entity : entities) {
        delete entity;
    }
    return 0;
}