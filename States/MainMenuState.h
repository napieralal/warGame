#pragma once

#include "GameState.h"
#include "../button.h"

class MainMenuState :
    public State
{
private:
    sf::Font font;
    sf::Text gameTitle;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initTitle();
    void initKeybinds();
    void initButtons();
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    void updateInput();
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

