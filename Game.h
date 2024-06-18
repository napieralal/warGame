#pragma once

#include "States/MainMenuState.h";

class Game
{
private:
	sf::RenderWindow *window;
	sf::Event event;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	sf::Clock dtClock;
	float dt;

	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();
public:
	Game();
	virtual ~Game();

	void endApplication();

	void updateDt();
	void updateSFMLEvent();
	void update();
	void render();
	void run();
};

