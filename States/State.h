#pragma once

#include "../Entities/Player.h"


class State
{
private:

protected:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int> *supportedKeys;
	std::map<std::string, int> keybinds;

	bool quitState;
	bool pauseState;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	std::map<std::string, sf::Texture> textures;

	virtual void initKeybinds() = 0;
	virtual void initBackground() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	void endState();
	void stopState();
	void unstopState();
	

	virtual void updateMousePosition();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

