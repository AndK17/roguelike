#include <map>
#include <string>
#include <vector>

#include "config.hpp"

void changePlayerSymbol(char s);

class Entity {
public:
    Entity(int x, int y, char symbol, int health, int damage, int color,
           std::string name, int bonusHealth, int bonusDamage);

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

    int getBonusHealth();
    void setBonusHealth(int hp);

    int getBonusDamage();
    void setBonusDamage(int dmg);

    virtual void move(int dx, int dy);

    virtual void attack(Entity &other);

protected:
    int x, y;
    char symbol;
    int health, damage, color;
    std::string name;
    int bonusHealth, bonusDamage;
};

class Player : public Entity {
public:
    Player(int x, int y);

    int getMaxHealth();
    void setMaxHealth(int tmp);
    void move(int dx, int dy, std::vector<std::vector<char>> &map);

    void attack(Entity &other) override;

    Entity *collisionWithEnemy(int dx, int dy, std::vector<Entity> &enemies);

    std::vector<Entity> neighbourWithEnemy(std::vector<Entity> &enemies);

private:
    int maxHealth;
};

class Enemy : public Entity {
public:
    Enemy(int x, int y, char symbol, int health, int damage, int color,
          std::string name);
};

class Wolf : public Enemy {
public:
    Wolf(int x, int y);
};

class Slime : public Enemy {
public:
    Slime(int x, int y);
};

class Goblin : public Enemy {
public:
    Goblin(int x, int y);
};

class Orc : public Enemy {
public:
    Orc(int x, int y);
};

class Vampire : public Enemy {
public:
    Vampire(int x, int y);
};

class Demon : public Enemy {
public:
    Demon(int x, int y);
};

class Chest : public Entity {
public:
    Chest(int bonusHealth, int bonusDamage);
};

void fighting(Player &player, Entity &enemy, int stage);

std::vector<int> chestFighting(Player &player, Entity &chest, int stage);

bool isRoomClear(std::vector<Entity> &enemies);