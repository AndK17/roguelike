#include <iostream>

#include "map.hpp"

int random(int upper, int lower) {
    static std::mt19937 mt{std::random_device{}()};
    return lower + mt() % (upper - lower + 1);
}

void Room::draw_map() {
    for (int i = 0; i < size; i++) {
        map[0][i] = glb::symbol["border"];
        map[i][0] = glb::symbol["border"];
        map[size - 1][i] = glb::symbol["border"];
        map[i][size - 1] = glb::symbol["border"];
    }

    if (get_left())
        map[size / 2][0] = glb::emptySymbol;
    if (get_up())
        map[0][size / 2] = glb::emptySymbol;
    if (get_right())
        map[size / 2][size - 1] = glb::emptySymbol;
    if (get_down())
        map[size - 1][size / 2] = glb::emptySymbol;
}

Room::Room(bool left, bool up, bool right, bool down) {
    map = std::vector<std::vector<char>>(size, std::vector<char>(size, glb::emptySymbol));
    set_left(left);
    set_up(up);
    set_right(right);
    set_down(down);

    draw_map();
    generate_obstacles();
}

std::vector<std::vector<char>> &Room::getMap() {
    return map;
}

bool Room::get_left() {
    return doors[0];
}

bool Room::get_up() {
    return doors[1];
}

bool Room::get_right() {
    return doors[2];
}

bool Room::get_down() {
    return doors[3];
}

bool Room::get_is_finish() {
    return is_finish;
}

int Room::get_room_num() {
    return room_num;
}

std::array<bool, 4> &Room::get_doors() {
    return doors;
}

std::vector<Entity> &Room::get_entities() {
    return entities;
}

void Room::set_left(bool tmp) {
    doors[0] = tmp;
    draw_map();
}

void Room::set_up(bool tmp) {
    doors[1] = tmp;
    draw_map();
}

void Room::set_right(bool tmp) {
    doors[2] = tmp;
    draw_map();
}

void Room::set_down(bool tmp) {
    doors[3] = tmp;
    draw_map();
}

void Room::set_is_finish(bool tmp) {
    is_finish = tmp;
}

void Room::set_room_num(int tmp) {
    room_num = tmp;
}

void Room::generate_obstacles() {
    int obstacles_count = random(6, 2);
    for (int i = 0; i < obstacles_count; i++) {
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

bool check_enemy_pos(int x, int y, std::vector<Entity> &entities) {
    for (auto entity : entities) {
        if (x == entity.getX() && y == entity.getY())
            return true;
    }
    return false;
}

void Room::generate_enemies(int len) {
    int enemies_count = random(5, 3);
    int section = len / 3;

    for (int i = 0; i < enemies_count; i++) {
        int typeEnemy = random(1);
        int x = random(glb::roomSize - 2, 1);
        int y = random(glb::roomSize - 2, 1);
        while (map[x][y] != glb::emptySymbol || (x == size / 2 && y == size / 2) || check_enemy_pos(x, y, entities)) {
            x = random(glb::roomSize - 2, 1);
            y = random(glb::roomSize - 2, 1);
        }

        switch ((room_num - 1) / section) {
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

int change_random_door(Room &room) {
    int c = 4;
    if (room.get_left())
        c -= 1;
    if (room.get_up())
        c -= 1;
    if (room.get_right())
        c -= 1;
    if (room.get_down())
        c -= 1;

    int n = random(c - 1);

    if (!room.get_left()) {

        if (n == 0) {

            room.set_left(true);
            return 0;
        } else
            n -= 1;
    }

    if (!room.get_up()) {

        if (n == 0) {
            room.set_up(true);
            return 1;
        } else
            n -= 1;
    }

    if (!room.get_right()) {

        if (n == 0) {
            room.set_right(true);
            return 2;
        } else
            n -= 1;
    }

    if (!room.get_down()) {

        if (n == 0) {
            room.set_down(true);
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
    int next_pos;

    for (int i{0}; i < len; i++) {
        room.set_room_num(i + 1);
        room.generate_enemies(len);
        if (i == len - 1)
            room.set_is_finish(true);
        if (i != len - 1)
            next_pos = change_random_door(room);

        map[x][y] = room;

        switch (next_pos) {
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