#pragma once

#include "Tile.h"
#include <random>
#include <ctime>

class TileMap
{
private:
	sf::RectangleShape shape;
	std::vector<Tile*> tiles;
	Tile* lastClickedTile{ nullptr };
public:
	TileMap(int width, int height, sf::RenderWindow* window);
	virtual ~TileMap();

	Tile* getClickedTile();

	bool isAnyTileHovered(const sf::Vector2f& mousePos);

	void update(const sf::Vector2f& mousePos, const float& dt, Turn current_Turn);
	void render(sf::RenderTarget* target);
};

