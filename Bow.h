#pragma once

#include "RangedWeapon.h"

class RangedWeapon;

class Bow :
    public RangedWeapon
{
private:

    //

public:

//Constructors and Destructor:

    Bow(const int level, const int value, const std::string& texture_file_path);
    virtual ~Bow();

//Functions:

    virtual Bow* clone();

    virtual void update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

