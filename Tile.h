#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"

enum tile_states { 
	TILE_BASE, TILE_CLICKED,
	TILE_HEALTH, TILE_GOLD, TILE_SWORD,
	TILE_PLAYER1_BASE, TILE_PLAYER1_WALL, TILE_PLAYER1_SPAWN,
	TILE_PLAYER2_BASE, TILE_PLAYER2_WALL, TILE_PLAYER2_SPAWN
};

enum Turn { PLAYER1_TURN, PLAYER2_TURN };


class Tile
{
private:
public:
	sf::CircleShape tile;
	sf::CircleShape *tileTexture;
	bool lastClicked;
	sf::Texture healthTexture;
	sf::Texture goldTexture;
	sf::Texture wallTexture;
	sf::Texture swordTexture;
	sf::Texture spawnTexture;

	float offsetX;
	float offsetY;
	float keytime;
	float keytimeMax;
	tile_states tileState;
	tile_states previousTileState;
	sf::Sprite sprite;
	int gridX, gridY;
	Tile(int grid_x, int grid_y, float offsetX, float offsetY, tile_states tile_state);
	virtual ~Tile();

	void updateKeytime(const float& dt);
	void updateTileBase(Turn current_Turn);
	void updateTileEnemy(Turn current_Turn);
	void updateTileState(Turn current_Turn);

	sf::Vector2f getPosition() const;

	void setTileTexture(const sf::Texture& texture, float offsetX, float offsetY);

	const bool isLastClicked() const;

	const bool isClicked() const;
	void setTileState(tile_states state);
	tile_states getTileState() const;
	void update(const sf::Vector2f& mousePos, const float& dt, Turn current_Turn);
	void render(sf::RenderTarget* target);
};

