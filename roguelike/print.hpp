#include "entities.hpp"
#include <Windows.h>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


void drawGame(std::vector<std::vector<char>>& map,
              std::vector<std::vector<char>>& map_clear,
              Player& player,
              std::vector<Entity*>& entities);


COORD makeCoord(int x, int y);