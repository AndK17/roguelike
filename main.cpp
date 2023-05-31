#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "roguelike/control.hpp"

// Generate a random number between min and max
int random(int min, int max) { return rand() % (max - min + 1) + min; }

int main() {
    srand(time(0));

    // Initialize player and enemies
    Player player(10, 10);
    // std::vector<Entity *> entities;
    // for (int i = 0; i < 10; i++) {
    //     int typeEnemy = random(1, 3);
    //     switch (typeEnemy) {
    //     case 1:
    //         entities.push_back(
    //             new Goblin(random(1, ROOM_SIZE - 2), random(1, ROOM_SIZE - 2)));
    //         break;

    //     case 2:
    //         entities.push_back(
    //             new Slime(random(1, ROOM_SIZE - 2), random(1, ROOM_SIZE - 2)));
    //         break;

    //     case 3:
    //         entities.push_back(
    //             new Wolf(random(1, ROOM_SIZE - 2), random(1, ROOM_SIZE - 2)));
    //         break;
    //     }
    // }

    system("cls");

    // Generate map
    Map map(3);
    Map map_clear(map);

    drawGame(map, map_clear, player);
    drawStatistics(player);

    // Game loop
    while (player.getHealth() > 0) {
        char input;
        input = _getwch();
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            playGame(map, map_clear, player, input);
        } else if (input == 27) {
            std::cout << std::endl
                      << "Goodbye!" << std::endl;
            return 0;
        }
    }

    player.setSymbol(deathPlayerSymbol);
    playGame(map, map_clear, player, '1');
    std::cout << std::endl
              << "Game over!" << std::endl;

    // Clean up
    for (auto entity : entities) {
        delete entity;
    }
    return 0;
}
