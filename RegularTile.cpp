#include "stdafx.h"
#include "RegularTile.h"

//Constructor and Destructor:

RegularTile::RegularTile
(
	int type, int grid_x, int grid_y, float grid_size_f, 
	const sf::Texture& texture, const sf::IntRect& texture_rect, 
	bool collision
)
	: Tile(type, grid_x, grid_y, grid_size_f, texture, texture_rect, collision)
{
	
}

RegularTile::~RegularTile()
{

}


//Accessors:

const std::string RegularTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top
		<< " " << this->collision;

	return ss.str();
}


//Functions:

void RegularTile::update(const float& dt)
{

}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}