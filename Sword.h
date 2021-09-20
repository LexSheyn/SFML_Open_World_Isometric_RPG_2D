#pragma once

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword :
    public MeleeWeapon
{
private:

    //

public:

//Constructors and Destructor:

    Sword
    (
        const int level, const int damage_min, const int damage_max, const float range,
        const int value,
        const std::string& texture_file_path
    );
    virtual ~Sword();

//Functions:

    virtual Sword* clone();

    virtual void update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

