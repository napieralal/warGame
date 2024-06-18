#include "Entity.h"
#include "../Game.h"

void Entity::initVariables()
{
    animationComponent = nullptr;
}

Entity::Entity()
    :position(0.f,0.f)
{
    initVariables();
}

Entity::~Entity()
{
    delete animationComponent;
}

void Entity::setTexture(sf::Texture& texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
    animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::setPosition(const float x, const float y)
{
    position.x = x;
    position.y = y;
    sprite.setPosition(x, y);
}

const sf::Vector2f Entity::getPosition() const
{
    return position;
}

void Entity::move(const float x, const float y)
{
    sprite.setPosition(position.x = x, position.y = y);
}

void Entity::update(const float& dt)
{
    
}

void Entity::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
