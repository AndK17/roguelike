#include <iostream>

#include "map.hpp"


int random(int upper, int lower) {
    static std::mt19937 mt{std::random_device{}()};
    return lower + mt() % (upper - lower + 1);
}

void Room::draw_map() {
    for (int i = 0; i < size; i++) {
        map[0][i] = glb::borderSymbol;
        map[i][0] = glb::borderSymbol;
        map[size - 1][i] = glb::borderSymbol;
        map[i][size - 1] = glb::borderSymbol;
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
    generate_enemies();
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

std::array<bool, 4> &Room::get_doors() {
    return doors;
}

std::vector<Entity> & Room::get_entiteis()
{
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

void Room::generate_obstacles()
{
    int obstacles_count = random(6, 2);
    for(int i = 0; i < obstacles_count; i++)
    {
        switch (random(5))
        {
        case 0:
            map[random(size-3, 2)][random(size-3, 2)] = glb::borderSymbol;
            break;
        case 1:
            {
            int pos = random(size-5, 2);
            int y = random(size-3, 2);
            for(int j = 0; j < 3; j++)
            {
                map[y][pos + j] = glb::borderSymbol;
            }
            }
            break;
        case 2:
            {
            int pos = random(size-5, 2);
            int x = random(size-3, 2);
            for(int j = 0; j < 3; j++)
            {
                map[pos + j][x] = glb::borderSymbol;
            }
            }
            break;
        case 3:
            {
            int pos = random(size-5, 2);
            int x = random(size-5, 2);
            for(int j = 0; j < 3; j++)
            {
                map[pos + j][x] = glb::borderSymbol;
            }
            pos = pos + 2;
            for(int j = 0; j < 3; j++)
            {
                map[pos][x + j] = glb::borderSymbol;
            }
            }
            break;
        case 4:
            {
            int pos = random(size-5, 2);
            int x = random(size-5, 2);
            for(int j = 0; j < 3; j++)
            {
                map[x][pos + j] = glb::borderSymbol;
            }
            pos = pos + 2;
            for(int j = 0; j < 3; j++)
            {
                map[x + j][pos] = glb::borderSymbol;
            }
            }
            break;
        case 5:
            {
            int pos = random(size-5, 2);
            int x = random(size-5, 2);
            for(int j = 0; j < 3; j++)
            {
                map[x][pos + j] = glb::borderSymbol;
            }
            for(int j = 0; j < 3; j++)
            {
                map[x + j][pos] = glb::borderSymbol;
            }
            }
            break;
        }
    }
}

bool check_enemy_pos(int x, int y, std::vector<Entity> &entities)
{
    for(auto entity: entities)
    {
        if (x == entity.getX() && y == entity.getY()) 
        return true;
    }
    return false;
}

void Room::generate_enemies()
{
    int enemies_count = random(10, 7);
    for (int i = 0; i < enemies_count; i++) {
        int typeEnemy = random(3, 1);
        int x = random(glb::roomSize - 2, 1);
        int y = random(glb::roomSize - 2, 1);
        while (map[x][y] != glb::emptySymbol || (x == size/2 && y == size/2) || check_enemy_pos(x, y, entities))
        {
            x = random(glb::roomSize - 2, 1);
            y = random(glb::roomSize - 2, 1);
        }
        
        switch (typeEnemy) {
        case 1:
            entities.push_back(
                Goblin(x, y));
            break;

        case 2:
            entities.push_back(
                Slime(x, y));
            break;

        case 3:
            entities.push_back(
                Wolf(x, y));
            break;
        }
    }
}

void Map::setNullMap() {
    map = std::vector<std::vector<Room>>(size, std::vector<Room>(size, NULL));
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

int Map::getSize() {
    return size;
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

int change_randrom_door(Room &room) {
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
        if (i != len - 1)
            next_pos = change_randrom_door(room);
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