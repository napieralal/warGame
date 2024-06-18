#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
	if (!backgroundTexture.loadFromFile("textures/background.png")) {
		throw ("Error: MainMenuState - Image not found");
	}
	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		throw("Error: MainMenuState - Font file not found");
	}
}

void MainMenuState::initTitle()
{
	gameTitle.setFont(font);
	gameTitle.setString("War Game");
	gameTitle.setCharacterSize(80);
	gameTitle.setFillColor(sf::Color(150, 100, 30, 255));
	gameTitle.setOutlineColor(sf::Color(180, 600, 30, 255));
	gameTitle.setOutlineThickness(2.f);
	gameTitle.setLetterSpacing(2.f);
	gameTitle.setStyle(sf::Text::Bold);
	gameTitle.setPosition(
		this->window->getSize().x / 2.f - gameTitle.getGlobalBounds().width / 2.f,
		150.f
	);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifstream("Config/mainmenustate_keybinds.ini");

	if (ifstream.is_open()) {
		std::string key = "";
		std::string codeKey = "";
		while (ifstream >> key >> codeKey) {
			keybinds[key] = supportedKeys->at(codeKey);
		}
	}
	ifstream.close();
}

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"] = new Button(
	850.f, 450.f, 200.f, 50.f,
	&this->font, "Start Game", 40,
	sf::Color(255, 255, 255, 255),    
	sf::Color(200, 200, 255, 255),   
	sf::Color(150, 150, 255, 255),    
	sf::Color(0, 0, 150, 0),        
	sf::Color(0, 0, 200, 0),        
	sf::Color(0, 0, 100, 0));        

	buttons["EXIT_STATE"] = new Button(
		850.f, 850.f, 200.f, 50.f,
		&this->font, "Exit Game", 40,
		sf::Color(255, 255, 255, 255),    
		sf::Color(200, 200, 255, 255),    
		sf::Color(150, 150, 255, 255),    
		sf::Color(0, 0, 150, 0),        
		sf::Color(0, 0, 200, 0),        
		sf::Color(0, 0, 100, 0));        
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states)
	: State(window, supportedKeys,states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initTitle();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::updateInput()
{
}

void MainMenuState::updateButtons()
{
	for (auto &it : buttons) {
		it.second->update(mousePositionView);
	}

	if (buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(window, supportedKeys, states));
	}

	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
}

void MainMenuState::update(const float& dt)
{
	updateMousePosition();
	updateInput();

	updateButtons();
	
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(background);

	target->draw(gameTitle);

	renderButtons(target);

}
