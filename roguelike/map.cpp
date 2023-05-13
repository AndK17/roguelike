#include <iostream>


#include "map.hpp"


int random_section(int upper, int lower)
{
    std::mt19937 mt{std::random_device{}()};
	return lower + mt()%(upper - lower + 1);
}

void Room::draw_map()
{
    for (int i = 0; i < size; i++) {
        map[0][i] = '#';
        map[i][0] = '#';
        map[size - 1][i] = '#';
        map[i][size - 1] = '#';
    }
    
    if (get_left())
        map[size/2][0] = ' ';
    if (get_up())
        map[0][size/2] = ' ';
    if (get_right())
        map[size/2][size - 1] = ' ';
    if (get_down())
        map[size - 1][size/2] = ' ';
}

Room::Room(bool left, bool up, bool right, bool down)
{
    map = std::vector<std::vector<char>>(size, std::vector<char>(size, ' '));
    set_left(left);
    set_up(up);
    set_right(right);
    set_down(down);

    draw_map();
}


std::vector<std::vector<char>> Room::getMap()
{
    return map;
}

bool Room::get_left() 
{
    return doors[0];
}

bool Room::get_up() 
{
    return doors[1];
}

bool Room::get_right() 
{
    return doors[2];
}

bool Room::get_down() 
{
    return doors[3];
}

std::array<bool, 4>& Room::get_doors()
{
    return doors;
}

void Room::set_left(bool tmp)
{
    doors[0] = tmp;
    draw_map();
}

void Room::set_up(bool tmp)
{
    doors[1] = tmp;
    draw_map();
}

void Room::set_right(bool tmp)
{
    doors[2] = tmp;
    draw_map();
}

void Room::set_down(bool tmp)
{
    doors[3] = tmp;
    draw_map();
}


void Map::setNullMap()
{
    map = std::vector<std::vector<Room>>(size, std::vector<Room>(size, NULL));
}


void Map::setLen(int len)
{
    if (len > 0)
    {
        len = len;
        size = len * 2 - 1;
        roomX = roomY = size / 2;
        Map::setNullMap();   
    }
}

void Map::setRoomX(int x)
{
    if (x >= 0 && x < size) {
        roomX = x;
    }
}

void Map::setRoomY(int y)
{
    if (y >= 0 && y < size) {
        roomY = y;
    }
}


int Map::getSize()
{
    return size;
}

int Map::getLen()
{
    return len;
}

int Map::getRoomX()
{
    return roomX;
}

int Map::getRoomY()
{
    return roomY;
}


std::vector<std::vector<Room>> Map::getMap()
{
    return map;
}

int change_randrom_door(Room& room)
{
    int c = 4;
    if (room.get_left()) c -= 1;
    if (room.get_up()) c -= 1;
    if (room.get_right()) c -= 1;
    if (room.get_down()) c -= 1;

    int n = random_section(c-1);
    
    if (!room.get_left())
    {
        
        if (n == 0)
        {
            
            room.set_left(true);
            return 0;
        }
        else n -= 1;
    }
    
    if (!room.get_up())
    {
        
        if (n == 0)
        {
            room.set_up(true);
            return 1;
        }
        else n -= 1;
    }
    
    if (!room.get_right())
    {
        
        if (n == 0)
        {
            room.set_right(true);
            return 2;
        }
        else n -= 1;
    }
    
    if (!room.get_down())
    {
        
        if (n == 0)
        {
            room.set_down(true);
            return 3;
        }
        else n -= 1;
    }
}

Map::Map(int len)
{
    setLen(len);
    int x = size / 2;
    int y = size / 2;
    Room room(false);
    int next_pos;
    
    for (int i{0}; i < len; i++)
    {
        if (i != len - 1)
            next_pos = change_randrom_door(room);
        map[x][y] = room;
        switch (next_pos)
        {
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