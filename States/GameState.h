#pragma once

#include "State.h"
#include "../PauseMenu.h"
#include "../EndGame.h"
#include "../TileMap.h"

//enum Turn {PLAYER1_TURN, PLAYER2_TURN};

class GameState :
    public State
{
private:
    sf::Font font;
    sf::Texture tileTexture;
    PauseMenu *pauseMenu;
    EndGame *endGameMenu;
    TileMap *map;

    Player *player1;
    Player *player2;

    Turn currentTurn;
    bool gameEnded;
    bool mousePressed;

    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initMap();
    void initPauseMenu();
    void initEndGameMenu(std::string end_game_message);
    void initTextures();
    void initPlayers();
public:
    GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();


    void updateInput();
    void endGame(const std::string& message);
    void fightPlayers(Tile* clickedTile, Player* player1, Player* player2);
    void playerAction(tile_states tile_state, sf::Vector2f new_player_pos, Tile* clicked_tile, Player* current_player,
                        Player* another_player);
    void buildingWall(tile_states tile_state, Player* player);
    void updatePlayerInput(const float& dt);
    bool playerCanMoveToTile(const Tile* tile, const sf::Vector2f newPlayerPos);
    void updatePauseMenuButtons();
    void updateEndGameMenuButton();
    void updateMap(const sf::Vector2f& mousePos, const float& dt);
    void updateTileEffect(const Tile* tile, Player* player);
    void update(const float& dt);
    void renderPlayerStats(sf::RenderTarget* target, Player* player, float x, sf::Color color, std::string player_name);
    void renderTurnInfo(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = nullptr);
};

