#pragma once

#include "State.h"
#include "TileMap.h"

class State;
class StateData;
class TileMap;
class Tile;
class Gui;

class EditorStateData
{
public:

//Constructors and Destructor: //No distructor

//  EditorStateData() {};

    //Variables:

    sf::View* view;

    sf::Font* font;

    std::map<std::string, int>* keybinds;

    float* keytime;
    float* keytimeMax;

    sf::Vector2i* mousePositionScreen;
    sf::Vector2i* mousePositionWindow;
    sf::Vector2f* mousePositionView;
    sf::Vector2i* mousePositionGrid;
};

class EditorMode
{
private:

protected:

	StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;

public:

//Constructors and Distructor:

	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

//Accessors:

    const bool getKeytime();
    const bool getKeytime(const float max_keytime);

//Functions:

    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;

    virtual void renderGui(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

