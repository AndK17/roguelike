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
    void drawMap();

    /// @brief Получение карты комнаты
    /// @return Карта комнаты
    std::vector<std::vector<char>> &getMap();

    /// @brief Получение информации о наличии двери слева
    /// @return Информация о наличии двери слева
    bool getLeft();

    /// @brief Получение информации о наличии двери сверху
    /// @return Информация о наличии двери сверху
    bool getUp();

    /// @brief Получение информации о наличии двери справа
    /// @return Информация о наличии двери справа
    bool getRight();

    /// @brief Получение информации о наличии двери снизу
    /// @return Информация о наличии двери снизу
    bool getDown();

    /// @brief Получение информации является ли конмата финишной
    /// @return Информация является ли конмата финишной
    bool getIsFinish();

    /// @brief Получение порядкового номера комнаты
    /// @return Порядковый номер комнаты
    int getRoomNum();

    /// @brief Получение инофрмации о дверях в виде массива
    /// @return Массив информации о наличии дверей(порядок: left, up, right, down)
    std::array<bool, 4> &getDoors();

    /// @brief Получение массива сущностей в комнате
    /// @return Массив сущностей в комнате
    std::vector<Entity> &getEntities();

    /// @brief Изменение информации о левой двери
    /// @param tmp Новое значение 
    void setLeft(bool tmp);

    /// @brief Изменение информации о верхней двери
    /// @param tmp Новое значение 
    void setUp(bool tmp);

    /// @brief Изменение информации о парвой двери
    /// @param tmp Новое значение  
    void setRight(bool tmp);

    /// @brief Изменение информации о нижней двери
    /// @param tmp Новое значение  
    void setDown(bool tmp);

    /// @brief Изменение информации о том является ли конмата финишной
    /// @param tmp Новое значение  
    void setIsFinish(bool tmp);

    /// @brief Изменение порядкого номера комнаты
    /// @param tmp Новое значение  
    void setRoomNum(int tmp);

    /// @brief Генерация препятствий
    void generateObstacles();

    /// @brief Генерация монстров в комнате
    /// @param len Длина подземелья 
    void generateEnemies(int len);

    /// @brief Генерация сундука в комнате
    void generateChest();

protected:
    int size = glb::roomSize;
    int roomNum = 0;
    bool isFinish = false;
    // порядок: left, up, right, down
    std::array<bool, 4> doors;
    std::vector<std::vector<char>> map;
    std::vector<Entity> entities;
};

/// @brief Класс карты подземелья
class Map {
public:
    /// @brief Конструктор класса карты подземелья
    /// @param len Длина подземелья
    Map(int len);

    /// @brief Получение длины подземелья
    /// @return Длина подземелья
    int getLen();

    /// @brief Получение X координаты текущей комнаты
    /// @return X координата текущей комнаты
    int getRoomX();

    /// @brief Получение Y координаты текущей комнаты
    /// @return Y координата текущей комнаты
    int getRoomY();

    /// @brief Получение карты подземелья
    /// @return Карта подземелья
    std::vector<std::vector<Room>> &getMap();

    /// @brief Изменение длины подземелья
    /// @param len Длина подземелья
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