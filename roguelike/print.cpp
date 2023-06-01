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
    std::vector<Entity> &roomEntities = map.getMap()[map.getRoomX()][map.getRoomY()].get_entities();
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
            if (c == glb::playerSymbol) {
                SetConsoleTextAttribute(hStdOut, glb::color["player"]);
            } else {
                for (auto iter = cbegin(glb::symbol); iter != cend(glb::symbol); ++iter) {
                    if (c == iter->second) {
                        SetConsoleTextAttribute(hStdOut, glb::color[iter->first]);
                    }
                }
            }
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }

    SetConsoleTextAttribute(hStdOut, glb::color_white);
}

void drawStatistics(Player &player, std::vector<Entity> &entities, int roomNum) {
    SetConsoleTextAttribute(hStdOut, glb::color_white);
    SetConsoleCursorPosition(hStdOut, getInfoCOORD(0));
    std::cout << "room " << roomNum;

    SetConsoleCursorPosition(hStdOut, getInfoCOORD(1));
    std::cout << glb::playerSymbol << " (" << player.getName()
              << ") - HP: " << player.getHealth()
              << ", Damage: " << player.getDamage();

    if (!entities.empty()) {
        for (int i = 0; i < entities.size(); ++i)
            if (entities[i].getSymbol() != glb::symbol["death"]) {
                SetConsoleCursorPosition(hStdOut, getInfoCOORD(i + 2));
                std::cout << glb::symbol[entities[i].getName()] << " (" << entities[i].getName()
                          << ") - HP: " << entities[i].getHealth()
                          << ", Damage: " << entities[i].getDamage();
            }
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
