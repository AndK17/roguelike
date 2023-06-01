#include "entities.hpp"

Entity::Entity(int x, int y, char symbol, int health, int damage, int color,
               std::string name)
    : x{x}, y{y} {
    setSymbol(symbol);
    setHealth(health);
    setDamage(damage);
    setColor(color);
    setName(name);
}

Entity::~Entity() {}

// Getters and setters for entity's position
int Entity::getX() const { return x; }
void Entity::setX(int x) { this->x = x; }
int Entity::getY() const { return y; }
void Entity::setY(int y) { this->y = y; }

// Getter and setter for the entity's symbol
char Entity::getSymbol() const { return symbol; }
void Entity::setSymbol(char c) { symbol = c; }

int Entity::getHealth() const { return health; }
void Entity::setHealth(int health) {
    if (health <= 0) {
        this->health = 0;
    } else {
        this->health = health;
    }
}

int Entity::getDamage() const { return damage; }
void Entity::setDamage(int damage) {
    if (damage <= 0) {
        this->damage = 0;
    } else {
        this->damage = damage;
    }
}

int Entity::getColor() const { return color; }
void Entity::setColor(int color) { this->color = color; }

std::string Entity::getName() const { return name; }
void Entity::setName(std::string name) { this->name = name; }

// Move the entity one square in the specified direction
void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::attack(Entity &other) {
    other.setHealth(other.getHealth() - getDamage());
}

// Player class, inherits from Entity
Player::Player(int x, int y)
    : Entity(x, y, glb::playerSymbol, 100, 30, glb::color["player"], "player") {}

// Moves the player, checking for collision with walls and enemies
void Player::move(int dx, int dy, std::vector<std::vector<char>> &map) {
    if (map[getX() + dx][getY() + dy] == glb::symbol["border"])
        return;

    // Move the player if no collision
    Entity::move(dx, dy);
}

void Player::attack(Entity &other) {
    other.setHealth(other.getHealth() - getDamage());
    if (other.getHealth() <= 0) {
        other.setSymbol('X');
    }
}

Entity *Player::collisionWithEnemy(int dx, int dy,
                                   std::vector<Entity> &enemies) {
    for (auto &enemy : enemies) {
        if (enemy.getX() == getX() + dx && enemy.getY() == getY() + dy) {
            return &enemy;
        }
    }
    return nullptr;
}

std::vector<Entity> Player::neighbourWithEnemy(std::vector<Entity> &enemies) {
    std::vector<Entity> neighbourEnenmies{};
    for (auto &enemy : enemies) {
        if (((enemy.getX() == getX() + 1 && enemy.getY() == getY()) ||
             (enemy.getX() == getX() - 1 && enemy.getY() == getY()) ||
             (enemy.getX() == getX() && enemy.getY() == getY() + 1) ||
             (enemy.getX() == getX() && enemy.getY() == getY() - 1)) &&
            (enemy.getHealth() > 0)) {
            neighbourEnenmies.push_back(enemy);
        }
    }
    return neighbourEnenmies;
}

Enemy::Enemy(int x, int y, char symbol, int health, int damage, int color,
             std::string name)
    : Entity(x, y, symbol, health, damage, color, name) {}

Wolf::Wolf(int x, int y)
    : Enemy(x, y, glb::symbol["wolf"], 40, 15, glb::color["wolf"], "wolf") {}

Slime::Slime(int x, int y)
    : Enemy(x, y, glb::symbol["slime"], 50, 20, glb::color["slime"], "slime") {}

Goblin::Goblin(int x, int y)
    : Enemy(x, y, glb::symbol["goblin"], 90, 35, glb::color["goblin"], "goblin") {}

Orc::Orc(int x, int y)
    : Enemy(x, y, glb::symbol["orc"], 110, 40, glb::color["orc"], "orc") {}

Vampire::Vampire(int x, int y)
    : Enemy(x, y, glb::symbol["vampire"], 160, 50, glb::color["vampire"], "vampire") {}

Demon::Demon(int x, int y)
    : Enemy(x, y, glb::symbol["demon"], 185, 60, glb::color["demon"], "demon") {}

void fighting(Player &player, Entity &enemy, int stage) {
    char player_symbol = glb::playerSymbol;
    char enemy_symbol = glb::symbol[enemy.getName()];
    switch (stage) {
    case 0:
        // player attack
        player.setSymbol(' ');
        player.attack(enemy);
        enemy.setSymbol(player_symbol);
        break;
    case 1:
        // player return
        if (enemy.getHealth() == 0) {
            enemy.setSymbol(glb::symbol["death"]);
        } else {
            enemy.setSymbol(enemy_symbol);
        }
        player.setSymbol(player_symbol);
        break;
    case 2:
        // enemy attack
        enemy.setSymbol(' ');
        enemy.attack(player);
        player.setSymbol(enemy_symbol);
        break;
    case 3:
        // enemy return
        player.setSymbol(player_symbol);
        enemy.setSymbol(enemy_symbol);
        break;
    }
}
