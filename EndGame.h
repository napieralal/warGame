#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "button.h"

class EndGame
{
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    Button *button;

public:
    EndGame(sf::RenderWindow &window, sf::Font &font);
    EndGame(sf::RenderWindow& window, sf::Font& font, std::string end_game_message);
    virtual ~EndGame();

    std::map<std::string, Button*> getButtons();

    const bool isButtonPressed();
    void addButton(const std::string key, float y, const std::string text);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
};

