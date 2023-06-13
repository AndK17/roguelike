#include "print.hpp"

/// @brief Обновление игры
/// @param map Карта подземелья
/// @param mapClear Очищенная карта подземелья
/// @param player Игрок
/// @param entities Сущности уровня
/// @param roomNum Номер комнаты
/// @param bonus Бонусное здоровье и бонусный урон
void updateGame(Map &map,
                Map &mapClear,
                Player &player,
                std::vector<Entity> &entities,
                int roomNum,
                std::vector<int> &bonus);

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
