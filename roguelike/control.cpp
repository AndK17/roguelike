#include "control.hpp"

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

    std::vector<std::vector<char>> &roomMap = map.getMap()[map.getRoomX()][map.getRoomY()].getMap();
    std::vector<Entity> &entities = map.getMap()[map.getRoomX()][map.getRoomY()].get_entiteis();

    if (player.getY() + dy == -1) {
        map.setRoomY(map.getRoomY() - 1);
        player.setY(glb::roomSize - 1);
        drawGame(map, map_clear, player);
        showStatistics(player, entities);
    } else if (player.getX() + dx == -1) {
        map.setRoomX(map.getRoomX() - 1);
        player.setX(glb::roomSize - 1);
        drawGame(map, map_clear, player);
        showStatistics(player, entities);
    } else if (player.getY() + dy == glb::roomSize) {
        map.setRoomY(map.getRoomY() + 1);
        player.setY(0);
        drawGame(map, map_clear, player);
        showStatistics(player, entities);
    } else if (player.getX() + dx == glb::roomSize) {
        map.setRoomX(map.getRoomX() + 1);
        player.setX(0);
        drawGame(map, map_clear, player);
        showStatistics(player, entities);
    } else {
        auto enemy = player.collisionWithEnemy(dx, dy, entities);
        if (!enemy) {
            player.move(dx, dy, roomMap);
            drawGame(map, map_clear, player);
            showStatistics(player, entities);
        } else {
            for (int i = 0; i < 4; ++i) {
                if (i == 2 && enemy->getHealth() <= 0) {
                    break;
                }

                fighting(player, *enemy, i);
                drawGame(map, map_clear, player);
                showStatistics(player, entities);
                if (i < 3) {
                    Sleep(500);
                }
            }
        }
    }
}
