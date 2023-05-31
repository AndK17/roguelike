#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "roguelike/control.hpp"


int main() {
    srand(time(0));

    // Initialize player and enemies
    Player player(glb::roomSize / 2, glb::roomSize / 2);

    system("cls");

    // Generate map
    Map map(3);
    Map map_clear(map);

    playGame(map, map_clear, player, '1');
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

    player.setSymbol(glb::deathPlayerSymbol);
    playGame(map, map_clear, player, '1');
    std::cout << std::endl
              << "Game over!" << std::endl;

    return 0;
}
