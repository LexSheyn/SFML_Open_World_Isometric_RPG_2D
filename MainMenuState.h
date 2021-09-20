#pragma once

#include "GameState.h"
#include "SettingsState.h"
#include "EditorState.h"

class MainMenuState :
    public State
{
private:

//private: Variables:
    
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Font font;
    sf::Font systemFont;

    std::map<std::string, gui::Button*> buttons;

//private: Functions:

    //Initialization funtcions:

    void initVariables();
    void initBackground(const std::string file_path);
    void initGui();

    //Clears the GUI elements and reinitializes the GUI.
    //@return void
    void resetGui();

public:

//Constructor and Destructor:

    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

//Functions:

    void updateInput(const float& dt);
    void updateButtons(const float& dt);    
    void update(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

