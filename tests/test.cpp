#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../roguelike/control.hpp"

// entities
TEST_CASE("Entity test") {
    Entity e = Entity(5, 7, '!', 100, 10, 0, "name", 11, 12);

    CHECK(e.getX() == 5);
    CHECK_THROWS_AS(e.setX(-1), std::invalid_argument);

    CHECK(e.getY() == 7);
    CHECK_THROWS_AS(e.setY(-1), std::invalid_argument);

    CHECK(e.getSymbol() == '!');

    CHECK(e.getHealth() == 100);
    e.setHealth(-1);
    CHECK(e.getHealth() == 0);

    CHECK(e.getColor() == 0);
    CHECK_THROWS_AS(e.setColor(16), std::invalid_argument);

    CHECK(e.getName() == "name");

    CHECK(e.getBonusHealth() == 11);
    e.setBonusHealth(-1);
    CHECK(e.getBonusHealth() == 0);

    CHECK(e.getBonusDamage() == 12);
    e.setBonusDamage(-1);
    CHECK(e.getBonusDamage() == 0);
}

TEST_CASE("Player test") {
    Player p = Player(1, 1);

    CHECK(p.getMaxHealth() == 100);

    p.setMaxHealth(50);
    CHECK(p.getMaxHealth() == 50);
    CHECK(p.getHealth() == 50);

    p.setMaxHealth(-1);
    CHECK(p.getMaxHealth() == 0);
    CHECK(p.getHealth() == 0);

    std::vector<Entity> ev;
    CHECK(p.collisionWithEnemy(0, 0, ev) == nullptr);

    CHECK(p.neighbourWithEnemy(ev).empty() == true);
}

TEST_CASE("fighting test") {
    Entity e = Entity(5, 7, '!', 100, 10, 0, "name", 11, 12);
    Player p = Player(1, 1);

    CHECK_THROWS_AS(fighting(p, e, -1), std::invalid_argument);
}

TEST_CASE("chestFighting test") {
    Entity e = Entity(5, 7, '!', 100, 10, 0, "name", 11, 12);
    Player p = Player(1, 1);

    CHECK_THROWS_AS(chestFighting(p, e, -1), std::invalid_argument);
}

TEST_CASE("isRoomClear test") {
    std::vector<Entity> ev;

    CHECK(isRoomClear(ev) == true);

    ev.push_back(Entity(5, 7, glb::symbol["death"], 100, 10, 0, "name", 11, 12));
    CHECK(isRoomClear(ev) == true);

    ev.push_back(Entity(5, 7, '@', 100, 10, 0, "name", 11, 12));
    CHECK(isRoomClear(ev) == false);
}