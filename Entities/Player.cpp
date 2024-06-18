#include "Player.h"

#include <stdlib.h>

void Player::initVariables()
{
	maxHealth = 100;
	health = 100;
	gold = 10;
	attack = 50;
}

Player::Player(float x, float y, sf::Texture &texture_sheet)
{
	initVariables();

	setPosition(x, y);

	createAnimationComponent(texture_sheet);
	animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 50, 50);
}

Player::~Player()
{
}

const int Player::getHealth() const
{
	return health;
}

const int Player::getMaxHealth() const
{
	return maxHealth;
}

const int Player::getAttack() const
{
	return attack;
}

const int Player::getGold() const
{
	return gold;
}

void Player::setHealth(float health)
{
	this->health = health;
}

void Player::addHealth(int health)
{
	this->health += health;
}

void Player::addMaxHealth(int health)
{
	this->maxHealth += health;
}

void Player::addAttack(int attack)
{
	this->attack += attack;
}

void Player::addGold(int gold)
{
	this->gold += gold;
}

void Player::respawn(float x, float y)
{
	setPosition(x, y);
}

void Player::update(const float& dt)
{
	//Entity::update(dt);

	animationComponent->play("IDLE", dt);
}
