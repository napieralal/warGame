#include "EndGame.h"

EndGame::EndGame(sf::RenderWindow& window, sf::Font& font, std::string end_game_message)
    : font(font)
{
    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) - 100.f));
    container.setFillColor(sf::Color(20, 20, 20, 150));
    container.setPosition(static_cast<float>(window.getSize().x) / 2.f - container.getSize().x / 2.f, 30.f);

    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255, 255, 255, 200));
    menuText.setCharacterSize(60);
    menuText.setString(end_game_message);
    menuText.setPosition(container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f, container.getPosition().y + 40.f);
    
    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = container.getPosition().x + container.getSize().x / 2.f - buttonWidth / 2.f;
    float buttonY = container.getPosition().y + container.getSize().y / 2.f - buttonHeight / 2.f;
    button = new Button(
        buttonX, buttonY, buttonWidth, buttonHeight,
        &this->font, "Exit", 60,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
    );
}

EndGame::~EndGame()
{
    delete button;
}

const bool EndGame::isButtonPressed()
{
    return button->isPressed();
}

void EndGame::update(const sf::Vector2f& mousePos)
{
    button->update(mousePos);
}

void EndGame::render(sf::RenderTarget& target)
{
    target.draw(background);
    target.draw(container);
    button->render(&target);
    target.draw(menuText);
}