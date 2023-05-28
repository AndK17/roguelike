#include <iostream>

#include "print.hpp"

static COORD topLeftCorner = makeCoord(0, 0);

// Make COORD
COORD makeCoord(int x, int y) {
  COORD coord = {(SHORT)x, (SHORT)y};
  return coord;
}

void drawGame(Map &map, Map &map_clear, Player &player,
              std::vector<Entity *> &entities) {

  std::vector<std::vector<char>> roomMap =
      map_clear.getMap()[map.getRoomX()][map.getRoomY()].getMap();

  for (auto entity : entities) {
    roomMap[entity->getX()][entity->getY()] = entity->getSymbol();
  }
  roomMap[player.getX()][player.getY()] = player.getSymbol();

  clearConsole();

  // Set console cursor at top left corner
  SetConsoleCursorPosition(hStdOut, topLeftCorner);

  for (auto row : roomMap) {
    for (auto c : row) {
      if (c == playerSymbol || c == deathPlayerSymbol) {
        SetConsoleTextAttribute(hStdOut, Player{0, 0}.getColor());
      } else if (c == enemySymbol["goblin"]) {
        SetConsoleTextAttribute(hStdOut, Goblin{0, 0}.getColor());
      } else if (c == enemySymbol["slime"]) {
        SetConsoleTextAttribute(hStdOut, Slime{0, 0}.getColor());
      } else if (c == enemySymbol["wolf"]) {
        SetConsoleTextAttribute(hStdOut, Wolf{0, 0}.getColor());
      } else if (c == borderSymbol) {
        SetConsoleTextAttribute(hStdOut, color_yellow);
      } else if (c == deathSymbol) {
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
  std::cout << playerSymbol << ": " << player.getHealth() << "HP " << std::endl;
}

void drawStatistics(Player &player, Entity &enemy) {
  SetConsoleTextAttribute(hStdOut, color_white);
  std::cout << playerSymbol << ": " << player.getHealth() << "HP" << std::endl;
  if (enemy.getSymbol() != deathSymbol) {
    std::cout << enemySymbol[enemy.getName()] << ": "<< enemy.getHealth() << "HP" << std::endl;
  }
}

void clearConsole() {
  SetConsoleCursorPosition(hStdOut, topLeftCorner);
  for (int i = 0; i < 25; ++i) {
    std::cout << "                                                     "
              << std::endl;
  }
}

void showStatistics(Player& player, std::vector<Entity*>& entities) {
    if (player.checkNeighbourWithEnemy(entities)) {
        Entity &enemy{player.neighbourWithEnemy(entities)};
        drawStatistics(player, enemy);
    } else {
        drawStatistics(player);
    }
}