#include "stdafx.h"
#include "VisionComponent.h"

// Constructors and Destructor:

VisionComponent::VisionComponent(sf::Vector2f position, const float range, sf::Vector2f direction)
{
	this->area = new Area(position, range, sf::Color::Red);

	this->range = range;

	this->direction = direction;
}

VisionComponent::~VisionComponent()
{
	// Deleting area
	delete this->area;
}


// Accessors:

const float& VisionComponent::getRange() const
{
	return this->area->getRadius();
}

const sf::Vector2f& VisionComponent::getDirection() const
{
	return this->direction;
}


// Functions:

void VisionComponent::update(sf::Vector2f position, sf::Vector2f direction, const float& dt)
{
	this->area->update(position, dt);

	this->direction = direction;

//	sf::Vector2f direction_norm = direction / static_cast<float>(std::sqrt(std::pow(direction.x, 2) + (direction.y, 2)));
//
//	this->direction = direction_norm * this->range;
}

void VisionComponent::update(sf::Vector2i position, sf::Vector2f direction, const float& dt)
{
	this->area->update(position, dt);

	this->direction = direction;
}

void VisionComponent::render(sf::RenderTarget& target)
{
	this->area->render(target);
}
