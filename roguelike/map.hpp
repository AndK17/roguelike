#include <array>
#include <random>
#include <vector>

#include "entities.hpp"

/// @brief Генерация случайного числа на отрезке
/// @param upper Верхняя граница отрезка
/// @param lower Нижняя граница отрезка
/// @return Случаейное число
int random(int upper, int lower = 0);


/// @brief Класс комнаты
class Room {
public:
    /// @brief Конструктор класса Room
    /// @param left Есть ли левая дверь
    /// @param up Есть ли верхняя дверь
    /// @param right Есть ли правая дверь
    /// @param down Есть ли нижняя дверь
    Room(bool left = false, bool up = false, bool right = false, bool down = false);

    /// @brief Отрисовка стен и дверей на карте
    void draw_map();

    /// @brief Получение карты комнаты
    /// @return Карта комнаты
    std::vector<std::vector<char>> &getMap();

    /// @brief Получение информации о наличии двери слева
    /// @return Информация о наличии двери слева
    bool get_left();

    /// @brief Получение информации о наличии двери сверху
    /// @return Информация о наличии двери сверху
    bool get_up();

    /// @brief Получение информации о наличии двери справа
    /// @return Информация о наличии двери справа
    bool get_right();

    /// @brief Получение информации о наличии двери снизу
    /// @return Информация о наличии двери снизу
    bool get_down();

    /// @brief Получение информации является ли конмата финишной
    /// @return Информация является ли конмата финишной
    bool get_is_finish();

    /// @brief Получение порядкового номера комнаты
    /// @return Порядковый номер комнаты
    int get_room_num();

    /// @brief Получение инофрмации о дверях в виде массива
    /// @return Массив информации о наличии дверей(порядок: left, up, right, down)
    std::array<bool, 4> &get_doors();

    /// @brief Получение массива сущностей в комнате
    /// @return Массив сущностей в комнате
    std::vector<Entity> &get_entities();

    /// @brief Изменение информации о левой двери
    /// @param tmp Новое значение 
    void set_left(bool tmp);

    /// @brief Изменение информации о верхней двери
    /// @param tmp Новое значение 
    void set_up(bool tmp);

    /// @brief Изменение информации о парвой двери
    /// @param tmp Новое значение  
    void set_right(bool tmp);

    /// @brief Изменение информации о нижней двери
    /// @param tmp Новое значение  
    void set_down(bool tmp);

    /// @brief Изменение информации о том является ли конмата финишной
    /// @param tmp Новое значение  
    void set_is_finish(bool tmp);

    /// @brief Изменение порядкого номера комнаты
    /// @param tmp Новое значение  
    void set_room_num(int tmp);

    /// @brief Генерация препятствий
    void generate_obstacles();

    /// @brief Генерация монстров в комнате
    /// @param len Длина лабиринта 
    void generate_enemies(int len);

    /// @brief Генерация сундука в комнате
    /// @param len Длина лабиринта 
    void generateChest(int len);

protected:
    int size = glb::roomSize;
    int room_num = 0;
    bool is_finish = false;
    // порядок: left, up, right, down
    std::array<bool, 4> doors;
    std::vector<std::vector<char>> map;
    std::vector<Entity> entities;
};

/// @brief Класс карты лабиринта
class Map {
public:
    /// @brief Конструктор класса карты лабиринта
    /// @param len Длина лабиринта
    Map(int len);

    /// @brief Получение длины лабиринта
    /// @return Длина лабиринта
    int getLen();

    /// @brief Получение X координаты текущей комнаты
    /// @return X координата текущей комнаты
    int getRoomX();

    /// @brief Получение Y координаты текущей комнаты
    /// @return Y координата текущей комнаты
    int getRoomY();

    /// @brief Получение карты лабиринта
    /// @return Карта лабиринта
    std::vector<std::vector<Room>> &getMap();

    /// @brief Изменение длины лабиринта
    /// @param len Длина лабиринта
    void setLen(int len);

    /// @brief Генерирует пустую карту
    void setNullMap();

    /// @brief Изменение X координаты текущей комнаты
    /// @param x Новое значение X координаты
    void setRoomX(int x);

    /// @brief Изменение Y координаты текущей комнаты
    /// @param y Новое значение Y координаты
    void setRoomY(int y);


private:
    int len;
    int size;
    std::vector<std::vector<Room>> map;
    int roomX, roomY;
};