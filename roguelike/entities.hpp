#include <vector>
#include <string>

static char playerSymbol = '@';
static char enemySymbol = 'E';
static char deathSymbol = 'X';

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
    void setDamage(int damage);

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

    void move(int dx, int dy, std::vector<Entity*>& enemies, std::vector<std::vector<char>>& map);

    void attack(Entity& other) override;

    bool checkCollisionWithEnemies(int dx, int dy, std::vector<Entity*>& enemies);

    Entity& collisionWithEnemy(int dx, int dy, std::vector<Entity*>& enemies);
};

class Enemy : public Entity {
public:
    Enemy(int x, int y);

    void attack(Entity& other) override;
};

void fighting(Player& player, Entity& enemy, char player_symbol, char enemy_symbol, int stage);