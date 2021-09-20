#include "stdafx.h"
#include "Area.h"

// private: Functions:

void Area::initVariables()
{
	this->radius = 0.f;
	this->colorAlpha = 50;
}


// Constructors and Destructor:

Area::Area(sf::Vector2f position, const float radius, sf::Color color)
{
	this->initVariables();

	this->radius = radius;
	color.a = this->colorAlpha;

	this->shape.setRadius(radius);
	this->shape.setPosition(position.x - radius, position.y - radius);
	this->shape.setFillColor(color);
}

Area::Area(sf::Vector2i position, const float radius, sf::Color color)
{
	this->initVariables();

	this->radius = radius;
	color.a = this->colorAlpha;

	this->shape.setRadius(radius);
	this->shape.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
	this->shape.setFillColor(color);
}

Area::~Area()
{

}


// Accessors:

const sf::FloatRect Area::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const float& Area::getRadius() const
{
	return this->radius;
}

const sf::Vector2f Area::getPosition() const
{
	return this->shape.getPosition();
}

const sf::Color Area::getColor() const
{
	return this->shape.getFillColor();
}


// Modifiers:

void Area::setRadius(const float radius)
{
	this->radius = radius;
	this->shape.setRadius(radius);
}

void Area::setPosition(const float x, const float y)
{
	this->shape.setPosition(x, y);
}

void Area::setPosition(const sf::Vector2f& position)
{
	this->shape.setPosition(position);
}

void Area::setColor(sf::Color color)
{
	color.a = this->colorAlpha;

	this->shape.setFillColor(color);
}

// Functions:

void Area::update(sf::Vector2f position, const float& dt)
{
	this->shape.setPosition(position.x - this->radius, position.y - this->radius);
}

void Area::update(sf::Vector2i position, const float& dt)
{
	this->shape.setPosition(sf::Vector2f(position.x - this->radius, position.y - this->radius));
}

void Area::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}