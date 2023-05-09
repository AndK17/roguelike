#include <vector>

class Entity {
public:
    Entity(int x, int y, char symbol, int health, int damage);

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
    void setDamage(int health);

    virtual void move(int dx, int dy);

    virtual void attack(Entity& other);

protected:
    int x, y;
    char symbol;
	int health, damage;
};

class Player : public Entity {
public:
    Player(int x, int y);

    void move(int dx, int dy, std::vector<Entity*>& entities, std::vector<std::vector<char>>& map);

    void attack(Entity& other);
};

class Enemy : public Entity {
public:
    Enemy(int x, int y);
    // Attacks the player if they are adjacent
    // void attack(Entity& other) {
    //     if (abs(getX() - other.getX()) <= 1 && abs(getY() - other.getY()) <= 1) {
    //         other.setHealth(other.getHealth() - this->damage);
    //     }
    // }
};