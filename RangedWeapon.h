#pragma once

#include "Weapon.h"

class RangedWeapon :
    public Weapon
{
private:

    //

protected:

    //

public:

// Constructors and Destructor:

    RangedWeapon(const int level, const int value, const std::string& texture_file_path);
    virtual ~RangedWeapon();

// Functions:

    virtual RangedWeapon* clone() = 0;
    void generate(const int level_min, const int level_max);

    virtual void update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

