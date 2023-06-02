#include "control.hpp"
#include <iostream>

void playGame(Map &map,
              Map &map_clear,
              Player &player,
              char input) {
    // Move the player
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
    int roomNum = room.get_room_num();
    std::vector<std::vector<char>> &roomMap = room.getMap();
    std::vector<Entity> &entities = room.get_entities();
    std::vector<Entity> neighbourEnemies;

    std::vector<int> bonus;

    if (isRoomClear(entities)) {
        room.generateChest(map.getLen());
    }

    if (player.getY() + dy == -1) {
        map.setRoomY(map.getRoomY() - 1);
        player.setY(glb::roomSize - 1);
        drawGame(map, map_clear, player);
        neighbourEnemies = player.neighbourWithEnemy(entities);
        drawStatistics(player, neighbourEnemies, roomNum, bonus);
    } else if (player.getX() + dx == -1) {
        map.setRoomX(map.getRoomX() - 1);
        player.setX(glb::roomSize - 1);
        drawGame(map, map_clear, player);
        neighbourEnemies = player.neighbourWithEnemy(entities);
        drawStatistics(player, neighbourEnemies, roomNum, bonus);
    } else if (player.getY() + dy == glb::roomSize) {
        map.setRoomY(map.getRoomY() + 1);
        player.setY(0);
        drawGame(map, map_clear, player);
        neighbourEnemies = player.neighbourWithEnemy(entities);
        drawStatistics(player, neighbourEnemies, roomNum, bonus);
    } else if (player.getX() + dx == glb::roomSize) {
        map.setRoomX(map.getRoomX() + 1);
        player.setX(0);
        drawGame(map, map_clear, player);
        neighbourEnemies = player.neighbourWithEnemy(entities);
        drawStatistics(player, neighbourEnemies, roomNum, bonus);
    } else {
        Entity *enemy = player.collisionWithEnemy(dx, dy, entities);
        if (!enemy || enemy->getSymbol() == glb::symbol["death"]) {
            player.move(dx, dy, roomMap);
            drawGame(map, map_clear, player);
            neighbourEnemies = player.neighbourWithEnemy(entities);
            drawStatistics(player, neighbourEnemies, roomNum, bonus);
        } else {
            for (int i = 0; i < 4; ++i) {
                if (i == 2 && enemy->getHealth() <= 0) {
                    break;
                }

                if (enemy->getName() == "chest") {
                    bonus = chestFighting(player, *enemy, i);
                } else {
                    fighting(player, *enemy, i);
                }
                drawGame(map, map_clear, player);
                neighbourEnemies = player.neighbourWithEnemy(entities);
                drawStatistics(player, neighbourEnemies, roomNum, bonus);
                if (i < 3) {
                    Sleep(500);
                }
            }
        }
    }
}
