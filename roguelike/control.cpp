#include "control.hpp"

void playGame(std::vector<std::vector<char>>& map,
              std::vector<std::vector<char>>& map_clear,
              Player& player,
              std::vector<Entity*>& entities,
              char input) {
    // Move the player
    int dx{0}, dy{0};
    if (input == 'w') dx = -1;
    else if (input == 'a') dy = -1;
    else if (input == 's') dx = 1;
    else if (input == 'd') dy = 1;

    if (!player.checkCollisionWithEnemies(dx, dy, entities)) {
        player.move(dx, dy, entities, map);
        drawGame(map, map_clear, player, entities);
    } else {
        Entity &enemy{player.collisionWithEnemy(dx, dy, entities)};
        for (int i = 0; i < 4; ++i) {
            if (i == 2 && enemy.getHealth() <= 0) {
                break;
            }
            fighting(player, enemy, playerSymbol, enemySymbol, i);
            drawGame(map, map_clear, player, entities);
            if (i < 3) {
                Sleep(500);
            }
        }
    }
}