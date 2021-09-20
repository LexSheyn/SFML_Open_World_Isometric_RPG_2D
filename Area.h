#pragma once

class Area
{
private:

// Variables:

	sf::CircleShape shape;
	float radius;
	int colorAlpha;

// private: Functions:

	void initVariables();

public:

// Constructors and Destructor:

	Area(sf::Vector2f position, const float radius, sf::Color color);
	Area(sf::Vector2i position, const float radius, sf::Color color);
	virtual ~Area();

// Accessors:

	const sf::FloatRect getGlobalBounds() const;
	const float& getRadius() const;
	const sf::Vector2f getPosition() const;
	const sf::Color getColor() const;

// Modifiers:

	void setRadius(const float radius);
	void setPosition(const float x, const float y);
	void setPosition(const sf::Vector2f& position);
	void setColor(sf::Color color);

// Functions:

	void update(sf::Vector2f position, const float& dt);
	void update(sf::Vector2i position, const float& dt);

	void render(sf::RenderTarget& target);
};

