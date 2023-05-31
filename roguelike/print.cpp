#include <iostream>

#include "print.hpp"

static COORD topLeftCorner = makeCoord(0, 0);

static COORD bottomLeftCorner = makeCoord(0, glb::roomSize + 1);

// Make COORD
COORD makeCoord(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    return coord;
}

COORD getInfoCOORD(int y) {
    COORD infoCOORD = makeCoord(glb::roomSize * 2 + 1, y);
    return infoCOORD;
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
    SetConsoleCursorPosition(hStdOut, getInfoCOORD(0));

    std::cout << glb::playerSymbol << " (" << player.getName()
              << ") - HP: " << player.getHealth()
              << ", Damage: " << player.getDamage() << std::endl;

    SetConsoleCursorPosition(hStdOut, bottomLeftCorner);
}

void drawStatistics(Player &player, std::vector<Entity> &entities) {
    SetConsoleTextAttribute(hStdOut, color_white);
    SetConsoleCursorPosition(hStdOut, getInfoCOORD(0));

    std::cout << glb::playerSymbol << " (" << player.getName()
              << ") - HP: " << player.getHealth()
              << ", Damage: " << player.getDamage() << std::endl;
    for (int i = 0; i < entities.size(); ++i)
        if (entities[i].getSymbol() != glb::deathSymbol) {
            SetConsoleCursorPosition(hStdOut, getInfoCOORD(i + 1));

            std::cout << glb::enemySymbol[entities[i].getName()] << " (" << entities[i].getName()
                      << ") - HP: " << entities[i].getHealth()
                      << ", Damage: " << entities[i].getDamage() << std::endl;
        }

    SetConsoleCursorPosition(hStdOut, bottomLeftCorner);
}

void clearConsole() {
    SetConsoleCursorPosition(hStdOut, topLeftCorner);
    for (int i = 0; i < 25; ++i) {
        std::cout << "                                                                                               "
                  << std::endl;
    }
}

void showStatistics(Player &player, std::vector<Entity> &entities) {
    std::vector<Entity> neighbourEnenmies = player.neighbourWithEnemy(entities);
    if (!neighbourEnenmies.empty()) {
        drawStatistics(player, neighbourEnenmies);
    } else {
        drawStatistics(player);
    }
}