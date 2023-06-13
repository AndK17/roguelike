#include "control.hpp"
#include <iostream>

void updateGame(Map &map,
                Map &mapClear,
                Player &player,
                std::vector<Entity> &entities,
                int roomNum,
                std::vector<int> &bonus) {
    drawGame(map, mapClear, player);
    std::vector<Entity> neighbourEnemies{player.neighbourWithEnemy(entities)};
    drawStatistics(player, neighbourEnemies, roomNum, bonus);
}

bool playGame(Map &map,
              Map &mapClear,
              Player &player,
              char input) {

    int dx{0}, dy{0};
    if (input == 'w')
        dx = -1;
    else if (input == 'a')
        dy = -1;
    else if (input == 's')
        dx = 1;
    else if (input == 'd')
        dy = 1;

    Room &room = map.getMap()[map.getRoomX()][map.getRoomY()];
    int roomNum = room.getRoomNum();
    std::vector<std::vector<char>> &roomMap = room.getMap();
    std::vector<Entity> &entities = room.getEntities();

    std::vector<int> bonus;

    if (isRoomClear(entities)) {
        room.generateChest();
    }

    if (player.getY() + dy == -1) {
        map.setRoomY(map.getRoomY() - 1);
        player.setY(glb::roomSize - 1);
        updateGame(map, mapClear, player, entities, roomNum, bonus);
    } else if (player.getX() + dx == -1) {
        map.setRoomX(map.getRoomX() - 1);
        player.setX(glb::roomSize - 1);
        updateGame(map, mapClear, player, entities, roomNum, bonus);
    } else if (player.getY() + dy == glb::roomSize) {
        map.setRoomY(map.getRoomY() + 1);
        player.setY(0);
        updateGame(map, mapClear, player, entities, roomNum, bonus);
    } else if (player.getX() + dx == glb::roomSize) {
        map.setRoomX(map.getRoomX() + 1);
        player.setX(0);
        updateGame(map, mapClear, player, entities, roomNum, bonus);
    } else {
        Entity *enemy = player.collisionWithEnemy(dx, dy, entities);
        if (!enemy || enemy->getSymbol() == glb::symbol["death"]) {
            player.move(dx, dy, roomMap);
            updateGame(map, mapClear, player, entities, roomNum, bonus);
        } else {
            for (int i = 0; i < 4; ++i) {
                if (i == 2 && enemy->getHealth() <= 0) {
                    break;
                }

                if (enemy->getName() == "chest") {
                    bonus = chestFighting(player, *enemy, i);
                    if (room.getIsFinish()) {
                        return true;
                    }
                } else {
                    fighting(player, *enemy, i);
                }
                updateGame(map, mapClear, player, entities, roomNum, bonus);
                if (i < 3) {
                    Sleep(500);
                }
            }
        }
    }
    return false;
}
