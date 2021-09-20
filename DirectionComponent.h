#pragma once

#include "MovementComponent.h"

enum class Directions
{
	Up_Left = 0,
	Up,
	Up_Right,
	Right,
	Down_Right,
	Down,
	Down_Left,
	Left
};

class DirectionComponent
{
private:

// Variables:

	Directions direction;
	sf::Vector2f directionVector;

// private: Functions:

	void initVariables();

public:

// Constructors and Destructor:

	DirectionComponent(sf::Vector2f direction_vector);
	DirectionComponent(sf::Vector2i direction_vector);
	virtual ~DirectionComponent();

// Accessors:

	const Directions& getDirection() const;
	const sf::Vector2f& getDirectionVector() const;

// Functions:

	const bool checkDirectionByMovement(Directions direction, sf::Vector2f& velocity);

	const bool checkDirectionByMouse(Directions direction, sf::Vector2f& mouse_position);
	const bool checkDirectionByMouse(Directions direction, sf::Vector2i& mouse_position);


	void update(sf::Vector2f velocity);

	void update(sf::Vector2f mouse_position, const float& dt);
	void update(sf::Vector2i mouse_position, const float& dt);
};

