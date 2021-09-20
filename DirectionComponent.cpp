#include "stdafx.h"
#include "DirectionComponent.h"

// private: Functions:

void DirectionComponent::initVariables()
{
	this->direction = Directions::Down;

	this->directionVector = sf::Vector2f(0.f, 0.f);
}


// Constructors and Destructor:
DirectionComponent::DirectionComponent(sf::Vector2f direction_vector)
{
	this->initVariables();

	this->directionVector = direction_vector;
}

DirectionComponent::DirectionComponent(sf::Vector2i direction_vector)
{
	this->initVariables();

	this->directionVector = sf::Vector2f(direction_vector);
}

DirectionComponent::~DirectionComponent()
{

}


// Accessors:

const Directions& DirectionComponent::getDirection() const
{
	return this->direction;
}

const sf::Vector2f& DirectionComponent::getDirectionVector() const
{
	return this->directionVector;
}

const bool DirectionComponent::checkDirectionByMovement(Directions direction, sf::Vector2f& velocity)
{
	switch (direction)
	{
	case Directions::Up_Left:

		if (velocity.x < 0.f && velocity.y < 0.f)
		{
			this->direction = direction;
			this->directionVector.x = -std::abs(velocity.x);
			this->directionVector.y = -std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Up:

		if (velocity.x == 0.f && velocity.y < 0.f)
		{
			this->direction = direction;
			this->directionVector.x = 0.f;
			this->directionVector.y = -std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Up_Right:

		if (velocity.x > 0.f && velocity.y < 0.f)
		{
			this->direction = direction;
			this->directionVector.x = std::abs(velocity.x);
			this->directionVector.y = -std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Right:

		if (velocity.x > 0.f && velocity.y == 0.f)
		{
			this->direction = direction;
			this->directionVector.x = std::abs(velocity.x);
			this->directionVector.y = 0.f;
			return true;
		}
		break;

	case Directions::Down_Right:

		if (velocity.x > 0.f && velocity.y > 0.f)
		{
			this->direction = direction;
			this->directionVector.x = std::abs(velocity.x);
			this->directionVector.y = std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Down:

		if (velocity.x == 0.f && velocity.y > 0.f)
		{
			this->direction = direction;
			this->directionVector.x = 0.f;
			this->directionVector.y = -std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Down_Left:

		if (velocity.x < 0.f && velocity.y > 0.f)
		{
			this->direction = direction;
			this->directionVector.x = -std::abs(velocity.x);
			this->directionVector.y = std::abs(velocity.y);
			return true;
		}
		break;

	case Directions::Left:

		if (velocity.x < 0.f && velocity.y == 0.f)
		{
			this->direction = direction;
			this->directionVector.x = -std::abs(velocity.x);
			this->directionVector.y = 0.f;
			return true;
		}
		break;
	}

	return false;
}

const bool DirectionComponent::checkDirectionByMouse(Directions direction, sf::Vector2f& mouse_position)
{
	// TO DO

	return false;
}

const bool DirectionComponent::checkDirectionByMouse(Directions direction, sf::Vector2i& mouse_position)
{
	// TO DO

	return false;
}


// Functions:

void DirectionComponent::update(sf::Vector2f velocity)
{
	this->directionVector = velocity;
}

void DirectionComponent::update(sf::Vector2f mouse_position, const float& dt)
{
	this->directionVector = mouse_position;
}

void DirectionComponent::update(sf::Vector2i mouse_position, const float& dt)
{
	this->directionVector = sf::Vector2f(mouse_position);
}
