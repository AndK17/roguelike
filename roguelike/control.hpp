#include "print.hpp"

/// @brief Контроль игры
/// @param map Карта подземелья
/// @param map_clear Очищенная карта подземелья
/// @param player Игрок
/// @param input Ввод пользователя
/// @return True, если игра пройдена, в противном случае False
bool playGame(Map &map,
              Map &map_clear,
              Player &player,
              char input);

/// @brief Победа в игре
void win();