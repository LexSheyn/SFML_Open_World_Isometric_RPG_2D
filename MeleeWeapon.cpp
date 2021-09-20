#include "stdafx.h"
#include "MeleeWeapon.h"

// Constructors and Destructor:

MeleeWeapon::MeleeWeapon
(
    const int level, const int damage_min, const int damage_max, const float range,
    const int value,
    const std::string& texture_file_path
)
	: Weapon(level, damage_min, damage_max, range, value, texture_file_path)
{
	this->type = ItemTypes::Melee_Weapon;
}

MeleeWeapon::~MeleeWeapon()
{

}


// Functions:

void MeleeWeapon::generate(const int level_min, const int level_max)
{
    this->level = std::rand() % (level_max - level_min + 1) + level_min;

    this->damageMin = this->level * (std::rand() % 2 + 1);

    this->damageMax = this->level * (std::rand() % 2 + 1) + this->damageMin;

    this->range = static_cast<float>(this->level + std::rand() % 10 + 50);

    this->value = this->level + this->damageMin + this->damageMax + static_cast<int>(this->range) + (std::rand() % this->level * 10);

    std::cout << "Weapon Level: " << this->level << std::endl;
    std::cout << "Weapon Damage Min: " << this->damageMin << std::endl;
    std::cout << "Weapon Damage Max: " << this->damageMax << std::endl;
    std::cout << "Weapon Range: " << this->range << std::endl;
    std::cout << "Weapon Value: " << this->value << std::endl;
}
