#include <vector>
#include <random>
#include <array>

const int MAP_SIZE = 20;

int random_section(int upper, int lower = 0);

std::vector<std::vector<char>> generateMap();

class Room
{
public:
    Room(bool left = false, bool up = false, bool right = false, bool down = false);
    void drow_map();
    std::vector<std::vector<char>> getMap();
    bool get_left();
    bool get_up();
    bool get_right();
    bool get_down();
    std::array<bool, 4>& get_doors();
    void set_left(bool tmp);
    void set_up(bool tmp);
    void set_right(bool tmp);
    void set_down(bool tmp);
protected:
    int size = 10;
    // порядок: left, up, right, down
    std::array<bool, 4> doors;
    std::vector<std::vector<char>> map;
};


class Map
{
public:
    Map(int len);
    void setLen(int len);
    void setNullMap();
    int getSize();
    std::vector<std::vector<Room>> getMap();
private:
    int len;
    int size;
    std::vector<std::vector<Room>> map;
};