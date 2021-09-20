#include "stdafx.h"
#include "Sword.h"

//Constructors and Destructor:

Sword::Sword
(
	const int level, const int damage_min, const int damage_max, const float range,
	const int value,
	const std::string& texture_file_path
)
	: MeleeWeapon(level, damage_min, damage_max, range, value, texture_file_path)
{
	this->weaponSprite.setOrigin
	(
		this->weaponSprite.getGlobalBounds().width / 2.f,
		this->weaponSprite.getGlobalBounds().height
	);

	this->damageMin = damage_min;
	this->damageMax = damage_max;
	this->range = range;

	// Timer
	this->attackTimerMax = 500; // Milliseconds
}

Sword::~Sword()
{

}


//Functions:

Sword* Sword::clone()
{
	return new Sword(*this);
}

void Sword::update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center)
{
	//Updating visual weapon
	this->weaponSprite.setPosition(center);

	float dX = mouse_position_view.x - this->weaponSprite.getPosition().x;
	float dY = mouse_position_view.y - this->weaponSprite.getPosition().y;

	const float PI = 3.141592f;
	float deg = atan2(dY, dX) * 180.f / PI;

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax)
	{
		this->weaponSprite.rotate(30.f);
	}
	else
	{
		this->weaponSprite.setRotation(deg + 90.f);
	}
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
	{
		target.draw(this->weaponSprite, shader);
	}
	else
	{
		target.draw(this->weaponSprite);
	}
}
