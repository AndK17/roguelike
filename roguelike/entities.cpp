#include "entities.hpp"


Entity::Entity(int x, int y, char symbol, int health, int damage) : x{x}, y{y} {
        setSymbol(symbol);
        setHealth(health);
        setDamage(damage);
}

Entity::~Entity() {}

// Getters and setters for entity's position
int Entity::getX() const {
    return x;
}
void Entity::setX(int x) {
    this->x = x;
}
int Entity::getY() const {
    return y;
}
void Entity::setY(int y) {
    this->y = y;
}

// Getter and setter for the entity's symbol
char Entity::getSymbol() const {
    return symbol;
}
void Entity::setSymbol(char c) {
    symbol = c;
}

int Entity::getHealth() const {
    return health;
}
void Entity::setHealth(int health) {
    if (health <= 0) {
        this->health = 0;
    }
    else {
        this->health = health;
    }
}

int Entity::getDamage() const {
    return damage;
}
void Entity::setDamage(int damage) {
    this->damage = damage;
}

// Move the entity one square in the specified direction
void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::attack(Entity &other) {
    other.setHealth(other.getHealth() - getDamage());
}



// Player class, inherits from Entity
Player::Player(int x, int y) : Entity(x, y, playerSymbol, 100, 50) {}

// Moves the player, checking for collision with walls and enemies
void Player::move(int dx, int dy, std::vector<Entity*>& enemies, std::vector<std::vector<char>>& map) {
    if (map[getX() + dx][getY() + dy] == '#') return;

    // Move the player if no collision
    Entity::move(dx, dy);
}

void Player::attack(Entity& other) {
    other.setHealth(other.getHealth() - getDamage());
    if (other.getHealth() <= 0) {
        other.setSymbol('X');
    }
}

bool Player::checkCollisionWithEnemies(int dx, int dy, std::vector<Entity*>& enemies) {
    for (auto enemy : enemies) {
        if (enemy->getX() == getX() + dx && enemy->getY() == getY() + dy && enemy->getHealth() > 0) {
            return true;
        }
    }
    return false;
}

Entity& Player::collisionWithEnemy(int dx, int dy, std::vector<Entity*> &enemies) {
    for (auto enemy: enemies) {
        if (enemy->getX() == getX() + dx && enemy->getY() == getY() + dy) {
            return *enemy;
        }
    }
}

// Enemy class, inherits from Entity
Enemy::Enemy(int x, int y) : Entity(x, y, enemySymbol, 60, 30) {}

void Enemy::attack(Entity &other) {
    other.setHealth(other.getHealth() - getDamage());
    if (other.getHealth() <= 0) {
        //GAME OVER
    }
}

void fighting(Player& player, Entity& enemy, char player_symbol, char enemy_symbol, int stage) {
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
                enemy.setSymbol(deathSymbol);
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
