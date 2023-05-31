#include "map.hpp"
#include <Windows.h>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void drawGame(Map &map, Map &map_clear, Player &player);

void drawStatistics(Player &player);

void drawStatistics(Player &player, std::vector<Entity> &entities);

void clearConsole();

void showStatistics(Player &player, std::vector<Entity> &entities);

COORD makeCoord(int x, int y);
