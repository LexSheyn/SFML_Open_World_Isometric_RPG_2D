#pragma once

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class EditorStateData;
class TileMap;
class Tile;

class DefaultEditorMode :
    public EditorMode
{
private:

//Variables:

    sf::Text cursorText;
    sf::RectangleShape sideBar;
    sf::RectangleShape selectorRect;
    gui::TextureSelector* textureSelector;
    sf::IntRect textureRect;
    bool collision;
    int type;
    int layer;
    bool tileAddLock;

//private: Functions:

    void initVariables();
    void initGui();

public:

//Constructors and Destructor:

    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

//Functions:

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

