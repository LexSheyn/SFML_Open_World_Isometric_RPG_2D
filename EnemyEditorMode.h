#pragma once

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class EditorStateData;
class TileMap;
class Tile;
class EnemySpawner;

class EnemyEditorMode :
    public EditorMode
{
private:

//Variables:

    sf::Text cursorText;
    sf::RectangleShape sideBar;
    sf::RectangleShape selectorRect;

    //TEST
    const sf::IntRect iR;

    int type;
    int amount;
    int32_t timeToSpawn;
    float distanceMax;

//private: Functions:

    void initVariables();
    void initGui();

public:

//Constructors and Destructor:

    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

//Functions:

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

