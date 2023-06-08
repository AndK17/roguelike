#include "entities.hpp"

char playerSymbol = '@';

void changePlayerSymbol(char s) {
    playerSymbol = s;
}


Entity::Entity(int x, int y, char symbol, int health, int damage, int color,
               std::string name, int bonusHealth, int bonusDamage)
    : x{x}, y{y} {
    setSymbol(symbol);
    setHealth(health);
    setDamage(damage);
    setColor(color);
    setName(name);
    setBonusHealth(bonusHealth);
    setBonusDamage(bonusDamage);
}

Entity::~Entity() {}

int Entity::getX() const { return x; }
void Entity::setX(int x) { this->x = x; }
int Entity::getY() const { return y; }
void Entity::setY(int y) { this->y = y; }

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

int Entity::getBonusHealth() {
    return bonusHealth;
}

void Entity::setBonusHealth(int hp) {
    if (hp > 0)
        bonusHealth = hp;
    else
        bonusHealth = 0;
}

int Entity::getBonusDamage() {
    return bonusDamage;
}

void Entity::setBonusDamage(int dmg) {
    if (dmg > 0)
        bonusDamage = dmg;
    else
        bonusDamage = 0;
}

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::attack(Entity &other) {
    other.setHealth(other.getHealth() - getDamage());
}

Player::Player(int x, int y)
    : Entity(x, y, playerSymbol, 100, 30, glb::color["player"], "player", 0, 0) {
    setMaxHealth(100);
}

int Player::getMaxHealth() {
    return maxHealth;
}

void Player::setMaxHealth(int tmp) {
    maxHealth = tmp;
}

void Player::move(int dx, int dy, std::vector<std::vector<char>> &map) {
    if (map[getX() + dx][getY() + dy] == glb::symbol["border"])
        return;

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
    : Entity(x, y, symbol, health, damage, color, name, 0, 0) {}

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

Chest::Chest(int bonusHealth, int bonusDamage) : Entity(glb::roomSize / 2, glb::roomSize / 2, glb::symbol["chest"], 1, 0, glb::color["chest"], "chest", bonusHealth, bonusDamage) {}

void fighting(Player &player, Entity &enemy, int stage) {
    char playerTmpSymbol = playerSymbol;
    char enemyTmpSymbol = glb::symbol[enemy.getName()];
    switch (stage) {
    case 0:
        player.setSymbol(' ');
        player.attack(enemy);
        enemy.setSymbol(playerTmpSymbol);
        break;
    case 1:
        if (enemy.getHealth() == 0) {
            enemy.setSymbol(glb::symbol["death"]);
        } else {
            enemy.setSymbol(enemyTmpSymbol);
        }
        player.setSymbol(playerTmpSymbol);
        break;
    case 2:
        enemy.setSymbol(' ');
        enemy.attack(player);
        player.setSymbol(enemyTmpSymbol);
        break;
    case 3:
        player.setSymbol(playerTmpSymbol);
        enemy.setSymbol(enemyTmpSymbol);
        break;
    }
}

std::vector<int> chestFighting(Player &player, Entity &chest, int stage) {
    char playerTmpSymbol = playerSymbol;
    char chestTmpSymbol = glb::symbol[chest.getName()];
    std::vector<int> bonus;
    switch (stage) {
    case 0:
        player.setSymbol(' ');
        player.attack(chest);
        chest.setSymbol(playerTmpSymbol);
        break;
    case 1:
        if (chest.getHealth() == 0) {
            chest.setSymbol(glb::symbol["death"]);
            player.setMaxHealth(player.getMaxHealth() + chest.getBonusHealth());
            player.setHealth(player.getMaxHealth());
            player.setDamage(player.getDamage() + chest.getBonusDamage());

            bonus.push_back(chest.getBonusHealth());
            bonus.push_back(chest.getBonusDamage());
        } else {
            chest.setSymbol(chestTmpSymbol);
        }
        player.setSymbol(playerTmpSymbol);

        break;
    }
    return bonus;
}

bool isRoomClear(std::vector<Entity> &enemies) {
    for (auto &enemy : enemies) {
        if (enemy.getName() == "chest" || enemy.getSymbol() != glb::symbol["death"]) {
            return false;
        }
    }
    return true;
}
