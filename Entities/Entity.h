#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <thread>

#include "SFML/Graphics.hpp"
#include "../Components/AnimationComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	AnimationComponent* animationComponent;
public:
	sf::Vector2f position;
	Entity();
	virtual ~Entity();

	void setTexture(sf::Texture &texture);
	void createAnimationComponent(sf::Texture &texture_sheet);

	virtual void setPosition(const float x, const float y);
	const sf::Vector2f getPosition() const;
	virtual void move(const float x, const float y);

	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);
};

