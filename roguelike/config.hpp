#include <map>
#include <string>

extern char playerSymbol;

namespace glb {
constexpr int roomSize = 20;
constexpr char emptySymbol = ' ';
constexpr char healthSymbol = '#';

constexpr int color_black = 0;
constexpr int color_dark_blue = 1;
constexpr int color_dark_green = 2;
constexpr int color_light_blue = 3;
constexpr int color_dark_red = 4;
constexpr int color_magenta = 5;
constexpr int color_orange = 6;
constexpr int color_light_gray = 7;
constexpr int color_gray = 8;
constexpr int color_blue = 9;
constexpr int color_green = 10;
constexpr int color_cyan = 11;
constexpr int color_red = 12;
constexpr int color_pink = 13;
constexpr int color_yellow = 14;
constexpr int color_white = 15;

inline std::map<std::string, char> symbol{
    {"wolf", 'W'},
    {"slime", 'S'},
    {"goblin", 'G'},
    {"orc", 'O'},
    {"vampire", 'V'},
    {"demon", 'D'},
    {"death", 'X'},
    {"deathPlayer", '!'},
    {"border", '#'},
    {"chest", 'C'}};

inline std::map<std::string, int> color{
    {"wolf", color_light_gray},
    {"slime", color_blue},
    {"goblin", color_green},
    {"orc", color_cyan},
    {"vampire", color_dark_red},
    {"demon", color_magenta},
    {"death", color_gray},
    {"deathPlayer", color_red},
    {"border", color_yellow},
    {"player", color_red},
    {"chest", color_white}};

} // namespace glb
