#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include "SFML/Graphics.hpp"

enum button_states{BUTTON_BASE = 0, BUTTON_HOVER, BUTTON_CLICK};

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textBaseColor;
		sf::Color textHoverColor;
		sf::Color textClickColor;

		sf::Color baseColor;
		sf::Color hoverColor;
		sf::Color clickColor;

		sf::Color outlineBaseColor;
		sf::Color outlineHoverColor;
		sf::Color outlineClickColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_base_color, sf::Color text_hover_color, sf::Color text_click_color,
			sf::Color base_color, sf::Color hover_color, sf::Color click_color,
			sf::Color outline_base_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_click_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		void setText(const std::string text);
		void setId(const short unsigned id);

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget* target);
	};


