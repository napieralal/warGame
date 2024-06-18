#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    float maxHealth;
    float health;
    float gold;
    float attack;

    void initVariables();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    const int getHealth() const;
    const int getMaxHealth() const;
    const int getAttack() const;
    const int getGold() const;
    void setHealth(float health);
    void addAttack(int attack);
    void addGold(int gold);

    void addHealth(int health);
    void addMaxHealth(int health);

    void respawn(float x, float y);

    virtual void update(const float& dt);
};

