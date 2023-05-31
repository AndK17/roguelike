#include <map>
#include <string>
#include <vector>

static char playerSymbol = '@';
static char deathSymbol = 'X';
static char deathPlayerSymbol = '!';

static std::map<std::string, char> enemySymbol{
    {"goblin", 'G'}, {"slime", 'S'}, {"wolf", 'W'}};

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

class Entity {
public:
    Entity(int x, int y, char symbol, int health, int damage, int color,
           std::string name);

    virtual ~Entity();

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    char getSymbol() const;
    void setSymbol(char c);

    int getHealth() const;
    void setHealth(int health);

    int getDamage() const;
    void setDamage(int damage);

    int getColor() const;
    void setColor(int color);

    std::string getName() const;
    void setName(std::string name);

    virtual void move(int dx, int dy);

    virtual void attack(Entity &other);

protected:
    int x, y;
    char symbol;
    int health, damage, color;
    std::string name;
};

class Player : public Entity {
public:
    Player(int x, int y);

    void move(int dx, int dy, std::vector<std::vector<char>> &map);

    void attack(Entity &other) override;

    bool checkCollisionWithEnemies(int dx, int dy,
                                   std::vector<Entity> &enemies);

    Entity &collisionWithEnemy(int dx, int dy, std::vector<Entity> &enemies);

    bool checkNeighbourWithEnemy(std::vector<Entity> &enemies);

    Entity &neighbourWithEnemy(std::vector<Entity> &enemies);
};

class Enemy : public Entity {
public:
    Enemy(int x, int y, char symbol, int health, int damage, int color,
          std::string name);
};

class Goblin : public Enemy {
public:
    Goblin(int x, int y);
};

class Slime : public Enemy {
public:
    Slime(int x, int y);
};

class Wolf : public Enemy {
public:
    Wolf(int x, int y);
};

void fighting(Player &player, Entity &enemy, int stage);