#include <iostream>

#include "print.hpp"

static COORD topLeftCorner = makeCoord(0, 0);

// Make COORD
COORD makeCoord(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    return coord;
}

void drawGame(Map &map, Map &map_clear, Player &player) {
    std::vector<Entity> &roomEntities = map.getMap()[map.getRoomX()][map.getRoomY()].get_entiteis();
    std::vector<std::vector<char>> roomMap =
        map_clear.getMap()[map.getRoomX()][map.getRoomY()].getMap();

    for (auto &entity : roomEntities) {
        roomMap[entity.getX()][entity.getY()] = entity.getSymbol();
    }
    roomMap[player.getX()][player.getY()] = player.getSymbol();

    clearConsole();

    // Set console cursor at top left corner
    SetConsoleCursorPosition(hStdOut, topLeftCorner);

    for (auto row : roomMap) {
        for (auto c : row) {
            if (c == glb::playerSymbol || c == glb::deathPlayerSymbol) {
                SetConsoleTextAttribute(hStdOut, Player{0, 0}.getColor());
            } else if (c == glb::enemySymbol["goblin"]) {
                SetConsoleTextAttribute(hStdOut, Goblin{0, 0}.getColor());
            } else if (c == glb::enemySymbol["slime"]) {
                SetConsoleTextAttribute(hStdOut, Slime{0, 0}.getColor());
            } else if (c == glb::enemySymbol["wolf"]) {
                SetConsoleTextAttribute(hStdOut, Wolf{0, 0}.getColor());
            } else if (c == glb::borderSymbol) {
                SetConsoleTextAttribute(hStdOut, color_yellow);
            } else if (c == glb::deathSymbol) {
                SetConsoleTextAttribute(hStdOut, color_gray);
            } else {
                SetConsoleTextAttribute(hStdOut, color_white);
            }
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }

    SetConsoleTextAttribute(hStdOut, color_white);
}

void drawStatistics(Player &player) {
    SetConsoleTextAttribute(hStdOut, color_white);
    std::cout << glb::playerSymbol << " (" << player.getName()
              << ") - HP: " << player.getHealth()
              << ", Damage:  " << player.getDamage() << std::endl;
}

void drawStatistics(Player &player, Entity &enemy) {
    SetConsoleTextAttribute(hStdOut, color_white);
    std::cout << glb::playerSymbol << " (" << player.getName()
              << ") - HP: " << player.getHealth()
              << ", Damage:  " << player.getDamage() << std::endl;
    if (enemy.getSymbol() != glb::deathSymbol) {
        std::cout << glb::enemySymbol[enemy.getName()] << " (" << enemy.getName()
                  << ") - HP: " << enemy.getHealth()
                  << ", Damage:  " << enemy.getDamage() << std::endl;
    }
}

void clearConsole() {
    SetConsoleCursorPosition(hStdOut, topLeftCorner);
    for (int i = 0; i < 25; ++i) {
        std::cout << "                                                     "
                  << std::endl;
    }
}

void showStatistics(Player &player, std::vector<Entity> &entities) {
    auto enemy = player.neighbourWithEnemy(entities);
    if (enemy) {
        drawStatistics(player, *enemy);
    } else {
        drawStatistics(player);
    }
}