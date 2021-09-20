#include "stdafx.h"
#include "RangedWeapon.h"

// Constructors and Destructor:

RangedWeapon::RangedWeapon(const int level, const int value, const std::string& texture_file_path)
	: Weapon(level, value, texture_file_path)
{
	this->type = ItemTypes::Ranged_Weapon;
}

RangedWeapon::~RangedWeapon()
{

}


// Functions:

void RangedWeapon::generate(const int level_min, const int level_max)
{
}
