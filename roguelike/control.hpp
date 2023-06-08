#include "print.hpp"

/// @brief Контроль игры
/// @param map Карта подземелья
/// @param mapClear Очищенная карта подземелья
/// @param player Игрок
/// @param input Ввод пользователя
/// @return True, если игра пройдена, в противном случае False
bool playGame(Map &map,
              Map &mapClear,
              Player &player,
              char input);

/// @brief Победа в игре
void win();