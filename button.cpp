#include "button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_base_color, sf::Color text_hover_color, sf::Color text_click_color,
	sf::Color base_color, sf::Color hover_color, sf::Color click_color,
	sf::Color outline_base_color, sf::Color outline_hover_color, sf::Color outline_click_color,
	short unsigned id)
{
	buttonState = BUTTON_BASE;
	this->id = id;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(base_color);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outline_base_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_base_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textBaseColor = text_base_color;
	this->textHoverColor = text_hover_color;
	this->textClickColor = text_click_color;

	this->baseColor = base_color;
	this->hoverColor = hover_color;
	this->clickColor = click_color;

	this->outlineBaseColor = outline_base_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineClickColor = outline_click_color;
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (buttonState == BUTTON_CLICK) {
		return true;
	}
	return false;
}

const std::string Button::getText() const
{
	return text.getString();
}

const short unsigned& Button::getId() const
{
	return id;
}

void Button::setText(const std::string text)
{
	this->text.setString(text);
}

void Button::setId(const short unsigned id)
{
	this->id = id;
}

void Button::update(const sf::Vector2f &mousePos)
{
	buttonState = BUTTON_BASE;

	if (shape.getGlobalBounds().contains(mousePos)) {
		buttonState = BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BUTTON_CLICK;
		}
	}

	switch (buttonState) {
	case BUTTON_BASE:{
		shape.setFillColor(baseColor);
		text.setFillColor(textBaseColor);
		shape.setOutlineColor(outlineBaseColor);
		break;
	}
	case BUTTON_HOVER: {
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;
	}
	case BUTTON_CLICK: {
		shape.setFillColor(clickColor);
		text.setFillColor(textClickColor);
		shape.setOutlineColor(outlineClickColor);
		break;
	}
	default: {
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
