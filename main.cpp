#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

#include "roguelike/map.hpp"
#include "roguelike/control.hpp"


// Generate a random number between min and max
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}


int main() {
    srand(time(0));

    // Initialize player and enemies
    Player player(10, 10);
    std::vector<Entity*> entities;
    for (int i = 0; i < 10; i++) {
        entities.push_back(new Enemy(random(1, MAP_SIZE - 2), random(1, MAP_SIZE - 2)));
    }

    // Generate map
    std::vector<std::vector<char>> map{generateMap()};

    system("cls");

    std::vector<std::vector<char>> map_clear{map};

    drawGame(map, map_clear, player, entities);

    // Game loop
    while (player.getHealth() > 0) {
        char input;
        input = _getwch();
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            playGame(map, map_clear, player, entities, input);
        }
        else if (input == 27) {
            std::cout << std::endl << "Goodbye!" << std::endl;
            return 0;
        }
    }

    // Game over
    std::cout << std::endl << "Game over!" << std::endl;

    // Clean up
    for (auto entity : entities) {
        delete entity;
    }
    return 0;
}
