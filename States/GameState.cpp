#include "GameState.h"

void GameState::initVariables()
{
	currentTurn = PLAYER1_TURN;
}

void GameState::initBackground()
{
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
	if (!backgroundTexture.loadFromFile("textures/background.png")) {
		throw ("Error: GameState - Background file not found");
	}
	background.setTexture(&backgroundTexture);
}

void GameState::initKeybinds()
{
	std::ifstream ifstream("Config/gamestate_keybinds.ini");

	if (ifstream.is_open()) {
		std::string key = "";
		std::string codeKey = "";
		while (ifstream >> key >> codeKey) {
			keybinds[key] = supportedKeys->at(codeKey);
		}
	}
	ifstream.close();
}

void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		throw("Error: GameState - Font file not found");
	}
}

void GameState::initMap()
{
	if (!tileTexture.loadFromFile("textures/wall.png")) {
		throw("Error: GameState - Tile texture file not found");
	}
	map = new TileMap(7.f, 10.f, window);
}

void GameState::initPauseMenu()
{
	pauseMenu = new PauseMenu(*window, font);
	pauseMenu->addButton("QUIT", 600.f, "Quit");
	pauseMenu->addButton("RESUME", 300.f, "Resume");
}

void GameState::initEndGameMenu(std::string end_game_message)
{
	endGameMenu = new EndGame(*window, font, end_game_message);
}

void GameState::initTextures()
{
	if (textures["PLAYER_SHEET1"].loadFromFile("textures/playeranimation1.png")) {
		//throw ("Error: GameState - Player texture not found");
	}
	if (textures["PLAYER_SHEET2"].loadFromFile("textures/playeranimation2.png")) {
		//throw ("Error: GameState - Player texture not found");
	}
}

void GameState::initPlayers()
{
	player1 = new Player(0, 0, textures["PLAYER_SHEET1"]);
	player1->respawn(925, 950);
	player2 = new Player(0, 0, textures["PLAYER_SHEET2"]);
	player2->respawn(925, 30);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys,states), mousePressed(false), gameEnded(false)
{
	initVariables();
	initBackground();
	initKeybinds();
	initFonts();
	initMap();
	initPauseMenu();
	initTextures();
	initPlayers();
}

GameState::~GameState()
{
	delete pauseMenu;
	delete player1;
	delete player2;
}

void GameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime()) {
		if (!pauseState) {
			stopState();
		}
		else {
			unstopState();
		}
	}
}

void GameState::endGame(const std::string& message)
{
	initEndGameMenu(message);
	gameEnded = true;
}

void GameState::fightPlayers(Tile *clickedTile ,Player *attacker, Player *defender)
{
	while (attacker->getHealth() > 0 && defender->getHealth() > 0) {
		std::cout<<attacker->getHealth()<<" "<<defender->getHealth()<<std::endl;
		defender->addHealth(-attacker->getAttack());
		attacker->addHealth(-defender->getAttack());
	}
	if (attacker->getHealth() <= 0 && defender->getHealth() <= 0) {
		if (attacker->getAttack() > defender->getAttack()) {
			attacker->setHealth(1);
			defender->setHealth(0);
			attacker->addGold(10);
			if(attacker == player1)
			{
				clickedTile->setTileState(TILE_PLAYER1_BASE);
			} else if(attacker == player2)
			{
				clickedTile->setTileState(TILE_PLAYER2_BASE);
			}
		} else{
			defender->setHealth(1);
			attacker->setHealth(0);
			defender->addGold(10);
			if(defender == player1)
			{
				clickedTile->setTileState(TILE_PLAYER1_BASE);
			} else if(defender == player2)
			{
				clickedTile->setTileState(TILE_PLAYER2_BASE);
			}
		}
	} else if (attacker->getHealth() <= 0)
	{
		defender->addGold(10);
		if(defender == player1)
		{
			clickedTile->setTileState(TILE_PLAYER1_BASE);
		} else if(defender == player2)
		{
			clickedTile->setTileState(TILE_PLAYER2_BASE);
		}
	} else
	{
		attacker->addGold(10);
		if(attacker == player1)
		{
			clickedTile->setTileState(TILE_PLAYER1_BASE);
		} else if(attacker == player2)
		{
			clickedTile->setTileState(TILE_PLAYER2_BASE);
		}
	}
}

void GameState::playerAction(tile_states tile_state, sf::Vector2f new_player_pos, Tile *clicked_tile,Player *current_player, Player *another_player)
{
	if(playerCanMoveToTile(clicked_tile, current_player->getPosition()))
	{
		updateTileEffect(clicked_tile, current_player);
		if(new_player_pos == another_player->getPosition())
		{
			current_player->setPosition(new_player_pos.x, new_player_pos.y);
			fightPlayers(clicked_tile, current_player, another_player);
		}
		else if(
			(current_player == player1 && tile_state != TILE_PLAYER2_WALL) ||
			(current_player == player2 && tile_state != TILE_PLAYER1_WALL))
		{
			clicked_tile->updateTileState(currentTurn);
			current_player->setPosition(new_player_pos.x, new_player_pos.y);
		} else if(
			(current_player == player1 && tile_state == TILE_PLAYER2_WALL) ||
			(current_player == player2 && tile_state == TILE_PLAYER1_WALL))
		{
			clicked_tile->updateTileState(currentTurn);
		}
						
		if(current_player == player1 && tile_state == TILE_PLAYER2_SPAWN)
		{
			endGame("Player 1 wins!");
		} else if(current_player == player2 && tile_state == TILE_PLAYER1_SPAWN)
		{
			endGame("Player 2 wins!");
		}
						
		if(current_player == player1 && (tile_state == TILE_PLAYER1_BASE || tile_state == TILE_PLAYER1_WALL || tile_state == TILE_PLAYER1_SPAWN))
		{
			return;
		}
		else if(current_player == player2 && (tile_state == TILE_PLAYER2_BASE || tile_state == TILE_PLAYER2_WALL || tile_state == TILE_PLAYER2_SPAWN))
		{
			return;
		}
		else if(currentTurn == PLAYER1_TURN)
		{
			currentTurn = PLAYER2_TURN;
		}
		else
		{
			currentTurn = PLAYER1_TURN;
		}
	}
}

void GameState::buildingWall(tile_states tile_state,Player *player)
{
	if(player->getGold() >= 10)
	{
		player->addGold(-10);
		if(player == player1)
		{
			currentTurn = PLAYER2_TURN;
		} else if(player == player2)
		{
			currentTurn = PLAYER1_TURN;
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!mousePressed) {
			mousePressed = true;
			Tile *clickedTile = map->getClickedTile();
			if (clickedTile)
			{
				sf::Vector2f newPlayerPos = clickedTile->getPosition();
				tile_states TileState = clickedTile->getTileState();
				newPlayerPos.x += 20.f;
				newPlayerPos.y += 20.f;
				
				if (currentTurn == PLAYER1_TURN) {
					playerAction(TileState, newPlayerPos, clickedTile, player1, player2);
				} else {
					playerAction(TileState, newPlayerPos, clickedTile, player2, player1);
				}
			}
		}
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!mousePressed) {
			mousePressed = true;
			const Tile* clickedTile = map->getClickedTile();
			if (clickedTile) {
				tile_states TileState = clickedTile->getTileState();
				if (currentTurn == PLAYER1_TURN) {
					buildingWall(TileState, player1);
				} else {
					buildingWall(TileState, player2);
				}
			}
		}
	}
	else {
		mousePressed = false;
	}
}

bool GameState::playerCanMoveToTile(const Tile* tile, const sf::Vector2f newPlayerPos)
{
	tile_states tileState = tile->getTileState();
	sf::Vector2f tilePos = tile->getPosition();
	float distance = std::sqrt(std::pow(newPlayerPos.x - tilePos.x , 2) + std::pow(newPlayerPos.y - tilePos.y , 2));
	if(distance <= 126.f)
	{
		return true;
	}
	return false;
}

void GameState::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPressed("QUIT")) {
		endState();
	}
	if(pauseMenu->isButtonPressed("RESUME"))
	{
		unstopState();
	}
}

void GameState::updateEndGameMenuButton()
{
	if (endGameMenu->isButtonPressed()) {
		endState();
	}
}

void GameState::updateMap(const sf::Vector2f& mousePos, const float &dt)
{
	map->update(mousePos, dt, currentTurn);
}

void GameState::updateTileEffect(const Tile* tile, Player* player)
{
	tile_states tileState = tile->getTileState();
	switch (tileState) {
	case TILE_SWORD:
		player->addAttack(10);
		break;
	case TILE_HEALTH:
		player->addHealth(20);
		player->addMaxHealth(10);
		break;
	case TILE_GOLD:
		player->addGold(10);
		break;
	case TILE_PLAYER1_WALL:
		if (player != player1) {
			player->addHealth(-10);
		}
		break;
	case TILE_PLAYER2_WALL:
		if (player != player2) {
			player->addHealth(-10);
		}
		break;
	default:
		break;
	}
}


void GameState::update(const float& dt)
{
	updateMousePosition();
	updateKeytime(dt);
	updateInput();

	updateMap(mousePositionView, dt);

	if(player1->getHealth() <= 0) {
		player1->respawn(925, 950);
		player1->setHealth(player1->getMaxHealth());
		currentTurn = PLAYER2_TURN;
	}
	if (player2->getHealth() <= 0) {
		player2->respawn(925, 30);
		player2->setHealth(player2->getMaxHealth());
		currentTurn = PLAYER1_TURN;
	}

	if(gameEnded)
	{
		endGameMenu->update(mousePositionView);
		updateEndGameMenuButton();
	}

	if (!pauseState) {
		updatePlayerInput(dt);

		player1->update(dt);
		player2->update(dt);
	}
	else {
		pauseMenu->update(mousePositionView);
		updatePauseMenuButtons();
	}

}

void GameState::renderPlayerStats(sf::RenderTarget *target, Player *player, float x, sf::Color color, std::string player_name)
{
	sf::Text playerStats;
	playerStats.setFont(font);
	playerStats.setCharacterSize(20);
	playerStats.setFillColor(color);
	playerStats.setString(player_name+"\nHealth: " + std::to_string(player->getHealth()) +
						   "\nGold: " + std::to_string(player->getGold()) +
						   "\nAttack: " + std::to_string(player->getAttack()));
	playerStats.setPosition(sf::Vector2f(
		target->getSize().x * x - playerStats.getGlobalBounds().width,
		target->getSize().y * 0.5f - playerStats.getGlobalBounds().height)
		);

	target->draw(playerStats);
}

void GameState::renderTurnInfo(sf::RenderTarget *target)
{
	sf::Text turnInfo;
	turnInfo.setFont(font);
	turnInfo.setCharacterSize(24);
	turnInfo.setFillColor(sf::Color::White);
	turnInfo.setPosition(10.f, 10.f);

	if (currentTurn == PLAYER1_TURN) {
		turnInfo.setString("Player 1's (GREEN) Turn");
	} else {
		turnInfo.setString("Player 2's (RED) Turn");
	}

	target->draw(turnInfo);
}

void GameState::render(sf::RenderTarget *target)
{
	if(gameEnded)
	{
		endGameMenu->render(*target);
	} else
	{
		if (!target) {
			target = this->window;
		}
		target->draw(background);
		map->render(target);
		player1->render(this->window);
		player2->render(this->window);

		renderPlayerStats(target, player1, 0.2f, sf::Color(202, 252, 200, 255), "Player 1");
		renderPlayerStats(target, player2, 0.85f, sf::Color(245, 146, 140, 255), "Player 2");

		renderTurnInfo(target);

		if (pauseState) {
			pauseMenu->render(*target);
		}
	}
	
}
