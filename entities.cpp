#include <iostream>
#include <vector>
#include <string>

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
void Entity::setDamage(int health) {
    this->damage = damage;
}

// Move the entity one square in the specified direction
void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

// Attack another entity if they are adjacent
void Entity::attack(Entity& other) {
    if (abs(getX() - other.getX()) <= 1 && abs(getY() - other.getY()) <= 1) {
        other.setHealth(other.getHealth() - getDamage());
    }
}



Player::Player(int x, int y) : Entity(x, y, '@', 100, 50) {}

// Moves the player, checking for collision with walls and enemies
void Player::move(int dx, int dy, std::vector<Entity*>& entities, std::vector<std::vector<char>>& map) {
    if (map[getX() + dx][getY() + dy] == '#') return;


    // Check for collision with enemies
    for (auto entity : entities) {
        if (entity->getX() == getX() + dx && entity->getY() == getY() + dy) {
            attack(*entity);
            // entity->attack(*this);
            return;
        }
    }

    // Move the player if no collision
    Entity::move(dx, dy);
}

// Attacks an enemy if they are adjacent
void Player::attack(Entity& other) {
    if (abs(getX() - other.getX()) <= 1 && abs(getY() - other.getY()) <= 1) {
        other.setHealth(other.getHealth() - getDamage());
        if (other.getHealth() <= 0) {
            other.setSymbol('X');
        }
    }
}


// Enemy class, inherits from Entity
Enemy::Enemy(int x, int y) : Entity(x, y, 'E', 40, 10) {}
