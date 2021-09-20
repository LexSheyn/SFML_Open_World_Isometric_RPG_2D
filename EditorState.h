#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"

enum class EditorModes : unsigned int
{
    Default = 0,
    Enemy
};

class EditorState :
    public State
{
private:

//private: Variables:

    EditorStateData editorStateData;

    sf::View view;
    sf::Vector2i viewGridPosition;
    float cameraSpeed;

    sf::Font font;
    PauseMenu* pauseMenu;    

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    std::vector<EditorMode*> modes;
    unsigned int activeMode;

//private: Functions:

    //Initialization funtcions:

    void initVariables();
    void initEditorStateData();
    void initView();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

    void initModes();

public:

//Constructors and Destructor:

    EditorState(StateData* state_data);
    virtual ~EditorState();

//Functions:

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons(const float& dt);
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void updateModes(const float& dt);
    void update(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

