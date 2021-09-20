#include "stdafx.h"
#include "AttributeComponent.h"

//Construcrors and Destructor:

AttributeComponent::AttributeComponent(int level)
{
	//Leveling
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (std::pow(this->level + 1, 3) - 6 * std::pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	//Attributes
	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}


//Accessors:

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}


//Functions:

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level
		<< "\n" << "Exp: " << this->exp
		<< "\n" << "Exp Next: " << this->expNext
		<< "\n" << "Attribute points: " << this->attributePoints
		<< "\n";

	return ss.str();
}

void AttributeComponent::loseHp(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void AttributeComponent::gainHp(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::loseExp(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
	{
		this->exp = 0;
	}
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;
	
	this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax			= 100 + this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin		= this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax		= this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence		= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::updateLevel()
{
	if (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (std::pow(this->level, 3) - 6 * std::pow(this->level, 2) + (this->level * 17) - 12));
		++this->attributePoints;
	}	
}

void AttributeComponent::update()
{
	this->updateLevel();
}