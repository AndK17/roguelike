#include "map.hpp"
#include <Windows.h>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

/// @brief Отрисовка игры
/// @param map Карта подземелья
/// @param mapClear Очищенная карта подземелья
/// @param player Игрок
void drawGame(Map &map, Map &mapClear, Player &player);

/// @brief Отрисовка статистики
/// @param player Игрок
/// @param entities Сущности
/// @param roomNum Номер комнаты
/// @param bonus Бонусное здоровье и бонусный урон
void drawStatistics(Player &player, std::vector<Entity> &entities, int roomNum, std::vector<int> bonus);

/// @brief Очистка консоли
void clearConsole();

/// @brief Создание координаты
/// @param x Координата по оси Ox (вертикаль)
/// @param y Координата по оси Oy (горизанталь)
/// @return Координата
COORD makeCoord(int x, int y);
