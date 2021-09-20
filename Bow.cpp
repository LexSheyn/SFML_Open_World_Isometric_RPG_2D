#include "stdafx.h"
#include "Bow.h"

//Constructors and Destructor:

Bow::Bow(const int level, const int value, const std::string& texture_file_path)
	: RangedWeapon(level, value, texture_file_path)
{
	
}

Bow::~Bow()
{

}


//Functions:

Bow* Bow::clone()
{
	return new Bow(*this);
}

void Bow::update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center)
{

}

void Bow::render(sf::RenderTarget& target, sf::Shader* shader)
{

}
