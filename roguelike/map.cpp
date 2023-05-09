#include <vector>

#include "map.hpp"

// Generate a random map with walls
std::vector<std::vector<char>> generateMap() {
    std::vector<std::vector<char>> map(MAP_SIZE, std::vector<char>(MAP_SIZE, ' '));

    // Add walls
    for (int i = 0; i < MAP_SIZE; i++) {
        map[0][i] = '#';
        map[i][0] = '#';
        map[MAP_SIZE - 1][i] = '#';
        map[i][MAP_SIZE - 1] = '#';
    }

    // // Add chests with random loot
    // for (int i = 0; i < 5; i++) {
    //     int x = random(1, MAP_SIZE - 2);
    //     int y = random(1, MAP_SIZE - 2);
    //     map[x][y] = 'C';
    // }

    return map;
}