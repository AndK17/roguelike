#include <map>
#include <string>

namespace glb {
constexpr char playerSymbol = '@';
constexpr char deathSymbol = 'X';
constexpr char deathPlayerSymbol = '!';

inline std::map<std::string, char> enemySymbol{
    {"goblin", 'G'}, {"slime", 'S'}, {"wolf", 'W'}};

constexpr int roomSize = 20;
constexpr char borderSymbol = '#';
constexpr char emptySymbol = ' ';

} // namespace glb

#define color_black 0
#define color_dark_blue 1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red 4
#define color_magenta 5
#define color_orange 6
#define color_light_gray 7
#define color_gray 8
#define color_blue 9
#define color_green 10
#define color_cyan 11
#define color_red 12
#define color_pink 13
#define color_yellow 14
#define color_white 15