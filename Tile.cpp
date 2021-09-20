#include "stdafx.h"
#include "Tile.h"

//Constructors and Destructor:

Tile::Tile()
{
	this->type = 0;
	this->collision = false;
}

Tile::Tile
(
	int type,
	int grid_x, int grid_y, float grid_size_f,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	const bool collision
)
{
//	this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
//	this->shape.setFillColor(sf::Color::White);
//	this->shape.setOutlineThickness(1.f);
//	this->shape.setOutlineColor(sf::Color::Black);

	this->type = type;

	this->collision = collision;

	this->shape.setPosition(static_cast<float>(grid_x) * grid_size_f, static_cast<float>(grid_y) * grid_size_f);

	this->shape.setTexture(texture);

	this->shape.setTextureRect(texture_rect);	
}

Tile::~Tile()
{

}

//Accessors:

const int& Tile::getType() const
{
	return this->type;
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions:

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}
