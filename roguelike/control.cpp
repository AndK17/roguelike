#include "control.hpp"

void playGame(Map &map,
              Map &map_clear,
              Player &player,
              std::vector<Entity *> &entities,
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

    std::vector<std::vector<char>> roomMap = map.getMap()[map.getRoomX()][map.getRoomY()].getMap();

    if (player.getY() + dy == -1) {
        map.setRoomY(map.getRoomY() - 1);
        player.setY(ROOM_SIZE - 1);
        drawGame(map, map_clear, player, entities);
        showStatistics(player, entities);
    } else if (player.getX() + dx == -1) {
        map.setRoomX(map.getRoomX() - 1);
        player.setX(ROOM_SIZE - 1);
        drawGame(map, map_clear, player, entities);
        showStatistics(player, entities);
    } else if (player.getY() + dy == ROOM_SIZE) {
        map.setRoomY(map.getRoomY() + 1);
        player.setY(0);
        drawGame(map, map_clear, player, entities);
        showStatistics(player, entities);
    } else if (player.getX() + dx == ROOM_SIZE) {
        map.setRoomX(map.getRoomX() + 1);
        player.setX(0);
        drawGame(map, map_clear, player, entities);
        showStatistics(player, entities);
    } else if (!player.checkCollisionWithEnemies(dx, dy, entities)) {
        player.move(dx, dy, entities, roomMap);
        drawGame(map, map_clear, player, entities);
        showStatistics(player, entities);
    } else {
        Entity &enemy{player.collisionWithEnemy(dx, dy, entities)};
        for (int i = 0; i < 4; ++i) {
            if (i == 2 && enemy.getHealth() <= 0) {
                break;
            }

            fighting(player, enemy, i);
            drawGame(map, map_clear, player, entities);
            showStatistics(player, entities);
            if (i < 3) {
                Sleep(500);
            }
        }
    }
}
