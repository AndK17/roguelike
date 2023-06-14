#include <map>
#include <string>
#include <vector>
#include <stdexcept>

#include "config.hpp"


/// @brief Смена символа игрока
/// @param s Новый символ
void changePlayerSymbol(char s);

/// @brief Класс сущности
class Entity {
public:
    /// @brief Конструктор класса Entity
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    /// @param symbol Отображаемый символ
    /// @param health Здоровье
    /// @param damage Наносимый урон
    /// @param color Цвет отображаемого символа
    /// @param name Имя
    /// @param bonusHealth Бонусное здоровье
    /// @param bonusDamage Бонусный урон
    Entity(int x, int y, char symbol, int health, int damage, int color,
           std::string name, int bonusHealth, int bonusDamage);

    /// @brief Деструктор класса Entity
    virtual ~Entity();

    /// @brief Получение координаты по оси Ox
    /// @return Координата по оси Ox
    int getX() const;

    /// @brief Установка координаты по оси Ox
    /// @param x Новая координата по оси Ox
    void setX(int x);

    /// @brief Получение координаты по оси Oy
    /// @return Координата по оси Oy
    int getY() const;

    /// @brief Установка координаты по оси Oy
    /// @param y Новая координата по оси Oy
    void setY(int y);

    /// @brief Получение отображаемого символа
    /// @return Отображаемый символ
    char getSymbol() const;

    /// @brief Установка отображаемого символа
    /// @param c Новый отображаемый символ
    void setSymbol(char c);

    /// @brief Получение здоровья
    /// @return Здороье
    int getHealth() const;

    /// @brief Установка здороья
    /// @param health Новое здоровье
    void setHealth(int health);

    /// @brief Получение наносимого урона
    /// @return Наносимый урон
    int getDamage() const;

    /// @brief Установка нансимого урона
    /// @param damage Новый наносимы урон
    void setDamage(int damage);

    /// @brief Получение цвета отображаемого символа
    /// @return Цвет отображаемого символа
    int getColor() const;

    /// @brief Установка цвета отображаемого символа
    /// @param color Новый отображаемый символ
    void setColor(int color);

    /// @brief Получение имени
    /// @return Имя
    std::string getName() const;

    /// @brief Установка имени
    /// @param name Новое имя
    void setName(std::string name);

    /// @brief Получение бонусного здоровья
    /// @return Бонусное здоровье
    int getBonusHealth() const;

    /// @brief Установка бонусного здоровья
    /// @param hp Новое бонусное здороье
    void setBonusHealth(int hp);

    /// @brief Получение бонусного урона
    /// @return Бонусный урон
    int getBonusDamage() const;

    /// @brief Установка бонусного урона
    /// @param dmg Новый бонусный урон
    void setBonusDamage(int dmg);

    /// @brief Перемещение
    /// @param dx Смещение по оси Ox
    /// @param dy Смещение по оси Oy
    virtual void move(int dx, int dy);

    /// @brief Атака
    /// @param other Атакуемая сущность
    virtual void attack(Entity &other);

protected:
    /// @brief Координата по оси Ox (вертикаль)
    int x;
    /// @brief Координата по оси Oy (горизанталь)
    int y;
    /// @brief Отображаемый символ
    char symbol;
    /// @brief Здоровье
    int health;
    /// @brief Наносимый урон
    int damage;
    /// @brief Цвет отображаемого символа
    int color;
    /// @brief Имя
    std::string name;
    /// @brief Бонусное здоровье
    int bonusHealth;
    /// @brief Бонусный урон
    int bonusDamage;
};

/// @brief Класс игрока
class Player : public Entity {
public:
    /// @brief Конструктор класса Player
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизонталь)
    Player(int x, int y);

    /// @brief Получение максимального здоровья
    /// @return Максимальное здоровье
    int getMaxHealth() const;

    /// @brief Установка максимального здоровья
    /// @param tmp Новое максимальное здоровья
    void setMaxHealth(int tmp);

    /// @brief Перемещение
    /// @param dx Смещение по оси Ox
    /// @param dy Смещение по оси Oy
    /// @param map Карта уровня
    void move(int dx, int dy, std::vector<std::vector<char>> &map);

    /// @brief Атака
    /// @param other Атакуемая сущность
    void attack(Entity &other) override;

    /// @brief Получение сущности, с которой произошла коллизия
    /// @param dx Смещение по оси Ox
    /// @param dy Смещение по оси Oy
    /// @param enemies Сущности уровня
    /// @return Сущность, с которой произошла коллизия
    Entity *collisionWithEnemy(int dx, int dy, std::vector<Entity> &enemies);

    /// @brief Получение граничных сущностей
    /// @param enemies Сущности уровня
    /// @return Сущности, которые граничат с игроком
    std::vector<Entity> neighbourWithEnemy(std::vector<Entity> &enemies);

private:
    /// @brief Максимальное здоровье
    int maxHealth;
};

/// @brief Класс врага
class Enemy : public Entity {
public:
    /// @brief Конструктор класса Enemy
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    /// @param symbol Отображаемый символ
    /// @param health Здоровье
    /// @param damage Наносимый урон
    /// @param color Цвет отображаемого символа
    /// @param name Имя
    Enemy(int x, int y, char symbol, int health, int damage, int color,
          std::string name);
};

/// @brief Класс волка
class Wolf : public Enemy {
public:
    /// @brief Конструктор класса Wolf
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Wolf(int x, int y);
};

/// @brief Класс слайма
class Slime : public Enemy {
public:
    /// @brief Конструктор класса Slime
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Slime(int x, int y);
};

/// @brief Класс гоблина
class Goblin : public Enemy {
public:
    /// @brief Конструктор класса Goblin
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Goblin(int x, int y);
};

/// @brief Класс орка
class Orc : public Enemy {
public:
    /// @brief Конструктор класса Orc
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Orc(int x, int y);
};

/// @brief Класс вампира
class Vampire : public Enemy {
public:
    /// @brief Конструктор класса Vampire
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Vampire(int x, int y);
};

/// @brief Класс демона
class Demon : public Enemy {
public:
    /// @brief Конструктор класса Demon
    /// @param x Координата по оси Ox (вертикаль)
    /// @param y Координата по оси Oy (горизанталь)
    Demon(int x, int y);
};

/// @brief Класс сундука
class Chest : public Entity {
public:
    /// @brief Конструктор класса Chest
    /// @param bonusHealth Бонусное здоровье
    /// @param bonusDamage Бонусный урон
    Chest(int bonusHealth, int bonusDamage);
};


/// @brief Битва с врагом
/// @param player Игрок
/// @param enemy Враг, с которым происходит битва
/// @param stage Стадия битвы
void fighting(Player &player, Entity &enemy, int stage);

/// @brief Битва с сундуком
/// @param player Игрок
/// @param chest Сундук, с которым происходит битва
/// @param stage Стадия битвы
/// @return Список с бонусным здоровьем и бонусным уроном
std::vector<int> chestFighting(Player &player, Entity &chest, int stage);

/// @brief Мертвы ли все враги в комнате
/// @param enemies Враги комнаты
/// @return true, если все враги в комнате мертвы, в противном случае false
bool isRoomClear(std::vector<Entity> &enemies);