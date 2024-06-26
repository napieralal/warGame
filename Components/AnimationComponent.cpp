#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : animations) {
		delete i.second;
	}
}

void AnimationComponent::addAnimation(
	const std::string key, 
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

void AnimationComponent::play(const std::string key, const float& dt)
{
	animations[key]->play(dt);
}
