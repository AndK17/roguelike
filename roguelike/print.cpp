#include <iostream>

#include "print.hpp"


static COORD topLeftCorner = makeCoord(0, 0);

// Make COORD
COORD makeCoord(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    return coord;
}

void drawGame(std::vector<std::vector<char>>& map,
              std::vector<std::vector<char>>& map_clear,
              Player& player,
              std::vector<Entity*>& entities) {
    map = map_clear;

    for (auto entity: entities) {
        map[entity->getX()][entity->getY()] = entity->getSymbol();
    }
    map[player.getX()][player.getY()] = player.getSymbol();

    // Set console cursor at top left corner
    SetConsoleCursorPosition(hStdOut, topLeftCorner);

    for (auto row: map) {
        for (auto c: row) {
            if (c == player.getSymbol()) {
                SetConsoleTextAttribute(hStdOut, 12);
            } else {
                SetConsoleTextAttribute(hStdOut, 15);
            }
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }

    // Print entities info
    std::cout << player.getSymbol() << ": (" << player.getX() << ", " << player.getY() << ") HP: "
              << player.getHealth() << "          " << std::endl;
    for (auto entity: entities) {
        std::cout << entity->getSymbol() << ": (" << entity->getX() << ", " << entity->getY() << ") HP: "
                  << entity->getHealth() << "          " << std::endl;
    }
}
