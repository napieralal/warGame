#include "Tile.h"

Tile::Tile(int grid_x, int grid_y, float offset_X, float offset_Y, tile_states tile_state)
    : gridX(grid_x), gridY(grid_y), keytimeMax(1.f), keytime(0.f), offsetX(offset_X), offsetY(offset_Y)
{
    tile = sf::CircleShape(50, 6);

    tile.setFillColor(sf::Color(194, 178, 128, 255));
    tile.setPosition(gridX * 88.6f + offset_X, gridY * 103.5f + offset_Y);
    tile.setOutlineThickness(1.f);
    tile.setOutlineColor(sf::Color(169, 158, 140));

    tileState = tile_state;
    previousTileState = tileState;

    healthTexture.loadFromFile("textures/health.png");
    goldTexture.loadFromFile("textures/gold.png");
    wallTexture.loadFromFile("textures/wall.png");
    swordTexture.loadFromFile("textures/sword.png");
    spawnTexture.loadFromFile("textures/base.png");
}

Tile::~Tile()
{
    delete tileTexture;
}

const bool Tile::isClicked() const
{
    return tileState == TILE_CLICKED;
}

void Tile::setTileState(tile_states state)
{
    tileState = state;
}

tile_states Tile::getTileState() const
{
    return previousTileState;
}

const bool Tile::isLastClicked() const{
    return lastClicked;
}

void Tile::updateKeytime(const float& dt)
{
    if (keytime < keytimeMax) {
        keytime += 10.f * dt;
    }
}

void Tile::updateTileBase(Turn current_Turn)
{
    if(current_Turn == PLAYER1_TURN)
    {
        if (tileState == TILE_BASE || tileState == TILE_GOLD || tileState == TILE_SWORD || tileState == TILE_HEALTH) {
            tileState = TILE_PLAYER1_BASE;
            tileTexture = nullptr;
            lastClicked = true;
        }
    } else
    {
        if (tileState == TILE_BASE || tileState == TILE_GOLD || tileState == TILE_SWORD || tileState == TILE_HEALTH) {
            tileState = TILE_PLAYER2_BASE;
            tileTexture = nullptr;
            lastClicked = true;
        } 
    }
}

void Tile::updateTileEnemy(Turn current_Turn)
{
    if(current_Turn == PLAYER1_TURN)
    {
        if (tileState == TILE_PLAYER2_BASE) {
            tileState = TILE_PLAYER1_BASE;
            lastClicked = true;
        }   else if(tileState == TILE_PLAYER2_WALL)
        {
            tileState = TILE_PLAYER2_BASE;
            tileTexture = nullptr;
            lastClicked = true;
        }
    } else
    {
        if (tileState == TILE_PLAYER1_BASE) {
            tileState = TILE_PLAYER2_BASE;
            lastClicked = true;
        }   else if(tileState == TILE_PLAYER1_WALL)
        {
            tileState = TILE_PLAYER1_BASE;
            tileTexture = nullptr;
            lastClicked = true;
        }
    }
}

void Tile::updateTileState(Turn current_Turn)
{
    updateTileBase(current_Turn);
    updateTileEnemy(current_Turn);
}

void Tile::update(const sf::Vector2f& mousePos, const float &dt, Turn current_Turn)
{
    updateKeytime(dt);
    previousTileState = tileState;
    if (tile.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && keytime >= keytimeMax) {
            keytime = 0.f;
            if(tileState == TILE_PLAYER1_SPAWN || tileState == TILE_PLAYER2_SPAWN)
            {
                lastClicked = true;
            }
            if (current_Turn == PLAYER1_TURN) {
                if (tileState == TILE_BASE || tileState == TILE_GOLD || tileState == TILE_SWORD || tileState == TILE_HEALTH) {
                    lastClicked = true;
                }
                else if(tileState == TILE_PLAYER1_WALL || tileState == TILE_PLAYER1_SPAWN || tileState == TILE_PLAYER1_BASE)
                {
                    lastClicked = true;
                }
                else if (tileState == TILE_PLAYER2_BASE) {
                    lastClicked = true;
                } else if(tileState == TILE_PLAYER2_WALL)
                {
                    lastClicked = true;
                }
            } else if (current_Turn == PLAYER2_TURN) {
                if (tileState == TILE_BASE || tileState == TILE_GOLD || tileState == TILE_SWORD || tileState == TILE_HEALTH) {
                    lastClicked = true;
                }
                else if(tileState == TILE_PLAYER2_WALL || tileState == TILE_PLAYER2_SPAWN || tileState == TILE_PLAYER2_BASE)
                {
                    lastClicked = true;
                }
                else if (tileState == TILE_PLAYER1_BASE) {
                    lastClicked = true;
                } else if(tileState == TILE_PLAYER1_WALL)
                {
                    lastClicked = true;
                }
            } else {
                lastClicked = false;
            }
        } else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && keytime >= keytimeMax) {
            keytime = 0.f;
            if (current_Turn == PLAYER1_TURN && tileState == TILE_PLAYER1_BASE)
            {
                tileState = TILE_PLAYER1_WALL;
                lastClicked = true;
            } else if(current_Turn == PLAYER2_TURN && tileState == TILE_PLAYER2_BASE)
            {
                tileState = TILE_PLAYER2_WALL;
                lastClicked = true;
            } else
            {
                lastClicked = false;
            }
        }
    } else {
        lastClicked = false;
    }

    switch (tileState) {
    case TILE_BASE:
        {
            tile.setFillColor(sf::Color(194, 178, 128, 255));
            break;
        }
    case TILE_HEALTH: {
        tile.setFillColor(sf::Color(194, 178, 128, 255));
        setTileTexture(healthTexture, offsetX, offsetY);
        break;
    }
    case TILE_GOLD: {
        tile.setFillColor(sf::Color(194, 178, 128, 255));
        setTileTexture(goldTexture, offsetX, offsetY);
        break;
    }
    case TILE_SWORD: {
        tile.setFillColor(sf::Color(194, 178, 128, 255));
        setTileTexture(swordTexture, offsetX, offsetY);
        break;
    }
    case TILE_PLAYER1_BASE: {
        tile.setFillColor(sf::Color(202, 252, 200, 255));
        break;
    }
    case TILE_PLAYER1_WALL: {
        tile.setFillColor(sf::Color(202, 252, 200, 255));
        setTileTexture(wallTexture, offsetX, offsetY);
        break;
    }
    case TILE_PLAYER1_SPAWN: {
        tile.setFillColor(sf::Color(202, 252, 200, 255));
        setTileTexture(spawnTexture, offsetX, offsetY);
        break;
    }
    case TILE_PLAYER2_BASE: {
        tile.setFillColor(sf::Color(245, 146, 140, 255));
        break;
    }
    case TILE_PLAYER2_WALL: {
        tile.setFillColor(sf::Color(245, 146, 140, 255));
        setTileTexture(wallTexture, offsetX, offsetY);
        break;
    }
    case TILE_PLAYER2_SPAWN: {
        tile.setFillColor(sf::Color(245, 146, 140, 200));
        setTileTexture(spawnTexture, offsetX, offsetY);
        break;
    }
    }
}

sf::Vector2f Tile::getPosition() const {
    return tile.getPosition();
}

void Tile::setTileTexture(const sf::Texture& texture, float offsetX, float offsetY)
{
    tileTexture = new sf::CircleShape(25);

    tileTexture->setTexture(&texture);
    float centerX = gridX * 88.6f + offsetX + 50;
    float centerY = gridY * 103.5f + offsetY + 50;
    tileTexture->setPosition(
        centerX - 23.f,
        centerY - 22.5f);
}

void Tile::render(sf::RenderTarget* target) {
    target->draw(tile);
    if (tileTexture) {
        target->draw(*tileTexture);
    }
}


