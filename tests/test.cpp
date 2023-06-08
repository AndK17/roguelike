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

TEST_CASE("Room test") {
    Room room{Room()};

    CHECK(room.getMap().size() == glb::roomSize);
    CHECK(room.getLeft() == false);
    CHECK(room.getUp() == false);
    CHECK(room.getRight() == false);
    CHECK(room.getDown() == false);
    CHECK(room.getIsFinish() == false);
    CHECK(room.getRoomNum() == 0);
    CHECK(room.getDoors() == std::array<bool, 4>{false, false, false, false});
    CHECK(room.getEntities().size() == 0);
    CHECK_THROWS_AS(room.generateEnemies(-3), std::invalid_argument);

    room.generateObstacles();
    bool wasBorder{false};
    for(int X = 1; X < room.getMap().size() - 1; X++)
    {
        for(int Y = 1; Y < room.getMap()[0].size() - 1; Y++)
        {
            if (room.getMap()[X][Y] == glb::symbol["border"]) {
                wasBorder = true;
                break;
            }
        }
    }
    CHECK(wasBorder == true);

    room.generateChest();
    bool wasChest = false;
    for (auto i: room.getEntities()) {
        if (i.getName() == "chest")
        {
            wasChest = true;
            break;
        }
    }
    CHECK(wasChest == true);
    
    room.setLeft(true);
    CHECK(room.getLeft() == true);

    room.setUp(true);
    CHECK(room.getUp() == true);

    room.setRight(true);
    CHECK(room.getRight() == true);

    room.setDown(true);
    CHECK(room.getDown() == true);

    room.setIsFinish(true);
    CHECK(room.getIsFinish() == true);

    room.setRoomNum(7);
    CHECK(room.getRoomNum() == 7);
    CHECK_THROWS_AS(room.setRoomNum(-5), std::invalid_argument);

    room.setRight(false);
    CHECK(room.getDoors() == std::array<bool, 4>{true, true, false, true});

}

TEST_CASE("Map test") {
    Map map{Map(5)};

    CHECK(map.getLen() == 5);
    CHECK_THROWS_AS(map.setLen(-1), std::invalid_argument);
    map.setLen(3);
    CHECK(map.getLen() == 3);


    map.setRoomX(4);
    CHECK(map.getRoomX() == 4);
    CHECK_THROWS_AS(map.setRoomX(-4), std::invalid_argument);
    CHECK_THROWS_AS(map.setRoomX(map.getLen()*10), std::invalid_argument);

    map.setRoomY(2);
    CHECK(map.getRoomY() == 2);
    CHECK_THROWS_AS(map.setRoomY(-4), std::invalid_argument);
    CHECK_THROWS_AS(map.setRoomY(map.getLen()*10), std::invalid_argument);

    map.setNullMap();
    std::array<bool, 4> noDoors{false, false, false, false};
    for(int X = 0; X < map.getMap().size(); X++)
    {
        for(int Y = 0; Y < map.getMap()[0].size(); Y++)
        {
            CHECK(map.getMap()[X][Y].getDoors() == noDoors);
        }
    }

}