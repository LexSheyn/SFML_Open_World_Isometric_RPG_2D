#pragma once

#include "Enemy.h"

class Rat :
    public Enemy
{
private:

// GUI:

    gui::ProgressBar* hpBar;

// private: Functions:

    void initVariables();
    void initAnimations();
    void initGui();

public:

// Constructors and Destructor:

    Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Rat();

// Accessors:

    //

// Functions:

    void updateGui(const float& dt);
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_position_view);

    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f shader_position = sf::Vector2f(), const bool show_hitbox = false);
};

