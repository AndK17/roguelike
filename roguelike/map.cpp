#include <iostream>

#include "map.hpp"

int random(int upper, int lower) {
    static std::mt19937 mt{std::random_device{}()};
    return lower + mt() % (upper - lower + 1);
}

void Room::drawMap() {
    for (int i = 0; i < size; i++) {
        map[0][i] = glb::symbol["border"];
        map[i][0] = glb::symbol["border"];
        map[size - 1][i] = glb::symbol["border"];
        map[i][size - 1] = glb::symbol["border"];
    }

    if (getLeft())
        map[size / 2][0] = glb::emptySymbol;
    if (getUp())
        map[0][size / 2] = glb::emptySymbol;
    if (getRight())
        map[size / 2][size - 1] = glb::emptySymbol;
    if (getDown())
        map[size - 1][size / 2] = glb::emptySymbol;
}

Room::Room(bool left, bool up, bool right, bool down) {
    map = std::vector<std::vector<char>>(size, std::vector<char>(size, glb::emptySymbol));
    setLeft(left);
    setUp(up);
    setRight(right);
    setDown(down);

    drawMap();
    generateObstacles();
}

std::vector<std::vector<char>> &Room::getMap() {
    return map;
}

bool Room::getLeft() {
    return doors[0];
}

bool Room::getUp() {
    return doors[1];
}

bool Room::getRight() {
    return doors[2];
}

bool Room::getDown() {
    return doors[3];
}

bool Room::getIsFinish() {
    return isFinish;
}

int Room::getRoomNum() {
    return roomNum;
}

std::array<bool, 4> &Room::getDoors() {
    return doors;
}

std::vector<Entity> &Room::getEntities() {
    return entities;
}

void Room::setLeft(bool tmp) {
    doors[0] = tmp;
    drawMap();
}

void Room::setUp(bool tmp) {
    doors[1] = tmp;
    drawMap();
}

void Room::setRight(bool tmp) {
    doors[2] = tmp;
    drawMap();
}

void Room::setDown(bool tmp) {
    doors[3] = tmp;
    drawMap();
}

void Room::setIsFinish(bool tmp) {
    isFinish = tmp;
}

void Room::setRoomNum(int tmp) {
    roomNum = tmp;
}

void Room::generateObstacles() {
    int obstaclesCount = random(6, 2);
    for (int i = 0; i < obstaclesCount; i++) {
        switch (random(5)) {
        case 0:
            map[random(size - 3, 2)][random(size - 3, 2)] = glb::symbol["border"];
            break;
        case 1: {
            int pos = random(size - 5, 2);
            int y = random(size - 3, 2);
            for (int j = 0; j < 3; j++) {
                map[y][pos + j] = glb::symbol["border"];
            }
        } break;
        case 2: {
            int pos = random(size - 5, 2);
            int x = random(size - 3, 2);
            for (int j = 0; j < 3; j++) {
                map[pos + j][x] = glb::symbol["border"];
            }
        } break;
        case 3: {
            int pos = random(size - 5, 2);
            int x = random(size - 5, 2);
            for (int j = 0; j < 3; j++) {
                map[pos + j][x] = glb::symbol["border"];
            }
            pos = pos + 2;
            for (int j = 0; j < 3; j++) {
                map[pos][x + j] = glb::symbol["border"];
            }
        } break;
        case 4: {
            int pos = random(size - 5, 2);
            int x = random(size - 5, 2);
            for (int j = 0; j < 3; j++) {
                map[x][pos + j] = glb::symbol["border"];
            }
            pos = pos + 2;
            for (int j = 0; j < 3; j++) {
                map[x + j][pos] = glb::symbol["border"];
            }
        } break;
        case 5: {
            int pos = random(size - 5, 2);
            int x = random(size - 5, 2);
            for (int j = 0; j < 3; j++) {
                map[x][pos + j] = glb::symbol["border"];
            }
            for (int j = 0; j < 3; j++) {
                map[x + j][pos] = glb::symbol["border"];
            }
        } break;
        }
    }
}

bool checkEnemyPos(int x, int y, std::vector<Entity> &entities) {
    for (auto entity : entities) {
        if (x == entity.getX() && y == entity.getY())
            return true;
    }
    return false;
}

void Room::generateEnemies(int len) {
    int enemiesCount = random(5, 3);
    int section = len / 3;

    for (int i = 0; i < enemiesCount; i++) {
        int typeEnemy = random(1);
        int x = random(glb::roomSize - 2, 1);
        int y = random(glb::roomSize - 2, 1);
        while (map[x][y] != glb::emptySymbol || (x == size / 2 && y == size / 2) || checkEnemyPos(x, y, entities)) {
            x = random(glb::roomSize - 2, 1);
            y = random(glb::roomSize - 2, 1);
        }

        switch ((roomNum - 1) / section) {
        case 0:
            if (typeEnemy == 0) {
                entities.push_back(Wolf(x, y));
            } else if (typeEnemy == 1) {
                entities.push_back(Slime(x, y));
            }
            break;

        case 1:
            if (typeEnemy == 0) {
                entities.push_back(Goblin(x, y));
            } else if (typeEnemy == 1) {
                entities.push_back(Orc(x, y));
            }
            break;
        case 2:
            if (typeEnemy == 0) {
                entities.push_back(Vampire(x, y));
            } else if (typeEnemy == 1) {
                entities.push_back(Demon(x, y));
            }
            break;
        }
    }
}

void Room::generateChest(int len) {
    switch (random(2)) {
    case 0:
        entities.push_back(Chest(20, 10));
        break;
    case 1:
        entities.push_back(Chest(35, 15));
        break;
    case 2:
        entities.push_back(Chest(50, 20));
        break;
    }
}

void Map::setNullMap() {
    map = std::vector<std::vector<Room>>(size, std::vector<Room>(size, Room()));
}

void Map::setLen(int len) {
    if (len > 0) {
        len = len;
        size = len * 2 - 1;
        roomX = roomY = size / 2;
        Map::setNullMap();
    }
}

void Map::setRoomX(int x) {
    if (x >= 0 && x < size) {
        roomX = x;
    }
}

void Map::setRoomY(int y) {
    if (y >= 0 && y < size) {
        roomY = y;
    }
}

int Map::getLen() {
    return len;
}

int Map::getRoomX() {
    return roomX;
}

int Map::getRoomY() {
    return roomY;
}

std::vector<std::vector<Room>> &Map::getMap() {
    return map;
}

int changeRandomDoor(Room &room) {
    int c = 4;
    if (room.getLeft())
        c -= 1;
    if (room.getUp())
        c -= 1;
    if (room.getRight())
        c -= 1;
    if (room.getDown())
        c -= 1;

    int n = random(c - 1);

    if (!room.getLeft()) {

        if (n == 0) {

            room.setLeft(true);
            return 0;
        } else
            n -= 1;
    }

    if (!room.getUp()) {

        if (n == 0) {
            room.setUp(true);
            return 1;
        } else
            n -= 1;
    }

    if (!room.getRight()) {

        if (n == 0) {
            room.setRight(true);
            return 2;
        } else
            n -= 1;
    }

    if (!room.getDown()) {

        if (n == 0) {
            room.setDown(true);
            return 3;
        } else
            n -= 1;
    }
    return 0;
}

Map::Map(int len) {
    setLen(len);
    int x = size / 2;
    int y = size / 2;

    Room room(false);
    int nextPos;

    for (int i{0}; i < len; i++) {
        room.setRoomNum(i + 1);
        room.generateEnemies(len);
        if (i == len - 1)
            room.setIsFinish(true);
        if (i != len - 1)
            nextPos = changeRandomDoor(room);

        map[x][y] = room;

        switch (nextPos) {
        case 0:
            y -= 1;
            room = Room(false, false, true);
            break;
        case 1:
            x -= 1;
            room = Room(false, false, false, true);
            break;
        case 2:
            y += 1;
            room = Room(true);
            break;
        case 3:
            x += 1;
            room = Room(false, true);
            break;
        }
    }
}