#pragma once

#include "Area.h"

class VisionComponent
{
private:

// Variables:

	Area* area;
	float range;
	sf::Vector2f direction;

public:

// Constructors and Destructor:

	VisionComponent(sf::Vector2f position, const float range, sf::Vector2f direction);
	virtual ~VisionComponent();

// Accessors:

	const float& getRange() const;
	const sf::Vector2f& getDirection() const;

// Functions:

	void update(sf::Vector2f position, sf::Vector2f direction, const float& dt);
	void update(sf::Vector2i position, sf::Vector2f direction, const float& dt);

	void render(sf::RenderTarget& target);
};

