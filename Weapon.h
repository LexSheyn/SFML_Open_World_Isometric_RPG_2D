#pragma once

#include "Item.h"

class Weapon :
    public Item
{
private:

// private: Functions:

    void initVariables();
    void initTexture(const std::string file_path);

protected:

// Variables:

    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;

    int damageMin;
    int damageMax;
    float range;

    sf::Clock attackTimer;
    int32_t attackTimerMax; // Milliseconds

public:

// Constructors and Destructor:

    Weapon(const int level, const int value, const std::string& texture_file_path);
    Weapon
    (
        const int level, const int damage_min, const int damage_max, const float range,
        const int value, 
        const std::string& texture_file_path
    );
    virtual ~Weapon();

// Accessors:

    const int& getDamageMin() const;
    const int& getDamageMax() const;
    const int getDamage() const;
    const float& getRange() const;
    const bool getAttackTimer();

// Functions:

    virtual Weapon* clone() = 0;
    virtual void generate(const int level_min, const int level_max) = 0;

    virtual void update(const sf::Vector2f& mouse_position_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

