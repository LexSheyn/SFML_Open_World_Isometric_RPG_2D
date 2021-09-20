#pragma once

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
    public Entity
{
private:

//Variables:

    EnemySpawnerTile& enemySpawnerTile;

//Initialization functions:

    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:

//Constructors and Destructor:

//    Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet);
    Enemy(EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Enemy();

//Accessors:

    EnemySpawnerTile& getEnemySpawnerTile() const;

//Functions:

    virtual void generateAttributes(const int level);

    virtual void playAnimation(std::string key, const float& dt, bool priority = false);

    virtual void updateAnimation(const float& dt) = 0;
    virtual void update(const float& dt, sf::Vector2f& mouse_position_view) = 0;

    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f shader_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

