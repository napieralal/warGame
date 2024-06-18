#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	quitState = false;
	pauseState = false;
	keytime = 0.f;
	keytimeMax = 10.f;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return quitState;
}

const bool State::getKeytime()
{
	if (keytime >= keytimeMax) {
		keytime = 0.f;
		return true;
	}

	return false;
}

void State::endState()
{
	quitState = true;
}

void State::stopState()
{
	pauseState = true;
}

void State::unstopState()
{
	pauseState = false;
}

void State::updateMousePosition()
{
	mousePositionScreen = sf::Mouse::getPosition();
	mousePositionWindow = sf::Mouse::getPosition(*window);
	mousePositionView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::updateKeytime(const float &dt)
{
	if (keytime < keytimeMax) {
		keytime += 100.f * dt;
	}
}
