#pragma once

#include "Entity.h"

#include "Items.h"
#include "Inventory.h"

class Entity;

class Player :
    public Entity
{
private:

//Variables:

    Inventory* inventory;

    bool attacking;
    Sword* sword;

//Initialization functions:

    void initVariables();
    void initAnimations();
    void initInventory();

public:

//Constructors and Destructor:

    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

//Accessors:

    Weapon* getWeapon() const;

//Functions:

    void playAnimation(std::string key, const float& dt, bool priority = false);

    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_position_view);

    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f shader_position = sf::Vector2f(), const bool show_hitbox = false);
};

