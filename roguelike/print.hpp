#include "map.hpp"
#include <Windows.h>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void drawGame(Map &map, Map &map_clear, Player &player);

void drawStatistics(Player &player, std::vector<Entity> &entities, int roomNum, std::vector<int> bonus);

void clearConsole();

COORD makeCoord(int x, int y);
