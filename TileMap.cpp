#include "TileMap.h"

tile_states getRandomTileState(std::default_random_engine& generator, std::uniform_int_distribution<int>& distribution)
{
    int randomTile = distribution(generator);
    switch (randomTile) {
    case 0:
        return TILE_GOLD;
    case 1:
        return TILE_SWORD;
    case 2:
        return TILE_HEALTH;
    default:
        return TILE_BASE;
    }
}

TileMap::TileMap(int width, int height, sf::RenderWindow* window) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, 2);

    shape.setSize({ static_cast<float>(width * 100.f), static_cast<float>(height * 105.f) });
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color(194, 178, 128));
    shape.setPosition(
        window->getSize().x / 2.f - shape.getGlobalBounds().width / 2.f,
        window->getSize().y / 2.f - shape.getGlobalBounds().height / 2.f - 10.f
    );

    float offsetX = shape.getPosition().x + 30.f;
    float offsetY = shape.getPosition().y;

    for (int j = 0; j < height; j++) {
        int rowWidth = width;

        if (j == 0 || j == height - 1) rowWidth = 1;
        else if (j == 1 || j == height - 2) rowWidth = 3;
        else if (j == 2 || j == height - 3) rowWidth = 5;

        int startX = (width - rowWidth) / 2;

        for (int i = 0; i < rowWidth; i++) {
            tile_states tileState = TILE_BASE;

            if (j == 9) {
                tileState = TILE_PLAYER1_SPAWN;

            }
            else if (j == 8) {
                tileState = TILE_PLAYER1_BASE;
            }
            else if (j == 0) {
                tileState = TILE_PLAYER2_SPAWN;
            }
            else if (j == 1) {
                tileState = TILE_PLAYER2_BASE;
            }
            else if ((j == 4 || j == 5) || ((j == 3 || j == 6) && (i == 0 || i == 2 || i == 4 || i == 6)) || ((j == 2 || j == 7) && (i == 2 || i == 0 || i == 4))) {
                tileState = getRandomTileState(generator, distribution);
            }

            tiles.push_back(new Tile(startX + i, j, offsetX, offsetY, tileState));
        }
    }
}

TileMap::~TileMap()
{
    for (auto& i : tiles) {
        delete i;
    }
}

Tile* TileMap::getClickedTile()
{
    for (auto& tile : tiles) {
        if (tile->isLastClicked()) {
            return tile;
        }
    }
    return nullptr;
}



bool TileMap::isAnyTileHovered(const sf::Vector2f& mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void TileMap::update(const sf::Vector2f& mousePos, const float &dt, Turn current_Turn) {
    for (auto& tile : tiles) {
        tile->update(mousePos, dt, current_Turn);
        if (tile->isClicked()) {
            lastClickedTile = tile;
        }
    }
}

void TileMap::render(sf::RenderTarget* target) {
    target->draw(shape);
    for (auto& tile : tiles) {
        tile->render(target);
    }
}
