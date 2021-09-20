#include "stdafx.h"
#include "Weapon.h"

// private: FUnctions:

void Weapon::initVariables()
{
	this->level = 0;
	this->damageMin = 0;
	this->damageMax = 0;
	this->range = 0.f;

	// Timer
	this->attackTimer.restart();
	this->attackTimerMax = 0; // Milliseconds
}

void Weapon::initTexture(const std::string file_path)
{
	if (!this->weaponTexture.loadFromFile(file_path))
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::initTexture::Failed to load " << file_path << std::endl;
	}
}


// Constructors and Destructor:

Weapon::Weapon(const int level, const int value, const std::string& texture_file_path)
	: Item(level, value)
{
	this->initVariables();

	this->initTexture(texture_file_path);

//	weaponTexture.loadFromFile("Resources/Images/Sprites/Player/sword.png");
//	weaponTexture.loadFromFile("Resources/Images/Sprites/Player/minigun_64x64_red_big.png");

	this->weaponSprite.setTexture(this->weaponTexture);
}

Weapon::Weapon(const int level, const int damage_min, const int damage_max, const float range, const int value, const std::string& texture_file_path)
	: Item{level, value}
{
	this->initVariables();

	this->damageMin = damage_min;
	this->damageMax = damage_max;
	this->range = range;

	this->initTexture(texture_file_path);

	this->weaponSprite.setTexture(this->weaponTexture);
}

Weapon::~Weapon()
{

}


// Accessors:

const int& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const int& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const int Weapon::getDamage() const
{
//	return rand() % (this->damageMax + 1) + this->damageMin;

	std::random_device seed;
	std::mt19937 random_damage(seed());
	std::uniform_int_distribution<int> generated(this->damageMin, this->damageMax);

	return generated(random_damage);
}

const float& Weapon::getRange() const
{
	return this->range;
}

const bool Weapon::getAttackTimer()
{
//	std::cout << "Attack timer: " << this->attackTimer.getElapsedTime().asMilliseconds() << std::endl;

	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}

	return false;
}
