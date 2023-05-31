#include <array>
#include <random>
#include <vector>

#include "entities.hpp"


int random(int upper, int lower = 0);

std::vector<std::vector<char>> generateMap();

class Room {
public:
    Room(bool left = false, bool up = false, bool right = false, bool down = false);
    void draw_map();
    std::vector<std::vector<char>> &getMap();
    bool get_left();
    bool get_up();
    bool get_right();
    bool get_down();
    std::array<bool, 4> &get_doors();
    std::vector<Entity> &get_entiteis();
    void set_left(bool tmp);
    void set_up(bool tmp);
    void set_right(bool tmp);
    void set_down(bool tmp);
    void generate_obstacles();
    void generate_enemies();

protected:
    int size = glb::roomSize;
    // порядок: left, up, right, down
    std::array<bool, 4> doors;
    std::vector<std::vector<char>> map;
    std::vector<Entity> entities;
};

class Map {
public:
    Map(int len);
    void setLen(int len);
    void setNullMap();
    void setRoomX(int x);
    void setRoomY(int y);
    int getSize();
    int getLen();
    int getRoomX();
    int getRoomY();
    std::vector<std::vector<Room>> &getMap();

private:
    int len;
    int size;
    std::vector<std::vector<Room>> map;
    int roomX, roomY;
};