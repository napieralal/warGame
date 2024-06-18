#include "Game.h"

void Game::initVariables()
{
	window = nullptr;
	fullscreen = false;
}

void Game::initWindow()
{
	std::ifstream ifstream("Config/window.ini");
	videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifstream.is_open()) {
		std::getline(ifstream, title);
		ifstream >> window_bounds.width >> window_bounds.height;
		ifstream >> fullscreen;
		ifstream >> framerate_limit;
		ifstream >> vertical_sync_enabled;
		ifstream >> antialiasing_level;
	}

	ifstream.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen) {
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	}
	else {
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	}
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifstream("Config/supported_keys.ini");

	if (ifstream.is_open()) {
		std::string key = "";
		int valueKey = 0;
		while (ifstream >> key >> valueKey) {
			supportedKeys[key] = valueKey;
		}
	}
	ifstream.close();
}

void Game::initStates()
{
	states.push(new MainMenuState(window, &supportedKeys, &states));
	//states.push(new GameState(window, &supportedKeys));
}


Game::Game()
{
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	delete window;

	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending application" << std::endl;
}


void Game::updateDt()
{

	dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvent()
{
	while(window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
}

void Game::update()
{
	updateSFMLEvent();

	if (!states.empty()) {
		states.top()->update(dt);

		if (states.top()->getQuit()) {
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	else {
		endApplication();
		window->close();
	}

}

void Game::render()
{
	window->clear();

	if (!states.empty()) {
		states.top()->render(window);
	}

	window->display();
}

void Game::run()
{
	while (window->isOpen()) {
		updateDt();
		update();
		render();
	}
}
