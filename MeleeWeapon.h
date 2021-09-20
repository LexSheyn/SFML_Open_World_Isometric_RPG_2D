#pragma once

#include "Weapon.h"

class MeleeWeapon :
    public Weapon
{
private:

protected:

// Variables:



public:

// Constructors and Destructor:

    MeleeWeapon
    (
        const int level, const int damage_min, const int damage_max, const float range,
        const int value,
        const std::string& texture_file_path
    );
    virtual ~MeleeWeapon();

// Functions:

    virtual MeleeWeapon* clone() = 0;
    void generate(const int level_min, const int level_max);

    virtual void update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

