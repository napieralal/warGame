#pragma once

#include <map>
#include <string>

#include "SFML/Graphics.hpp"

class AnimationComponent
{
private:
	class Animation
	{
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite &sprite, sf::Texture& texture_sheet,
			float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet),
			animationTimer(animation_timer), width(width), height(height)
		{
			timer = 0.f;
			startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			currentRect = this->startRect;
			endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}
		~Animation() {}

		void play(const float& dt) {
			timer += 10.f * dt;
			if (timer >= animationTimer) {

				timer = 0.f;

				if (currentRect != endRect) {
					currentRect.left += width;
				}
				else {
					currentRect.left = startRect.left;
				}

				sprite.setTextureRect(currentRect);
			}
		}

		void reset() {
			timer = 0.f;
			currentRect = startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
public:
	AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
	virtual ~AnimationComponent();

	void addAnimation(
		const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	void play(const std::string key, const float& dt);
};

