#pragma once

#include "State.h"

class SettingsState :
    public State
{
private:

//private: Variables:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Font font;
    sf::Font settingsFont;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText[4];

    std::vector<sf::VideoMode> modes;

//private: Functions:

    //Initialization funtcions:

    void initVariables();
    void initBackground(const std::string file_path);
    void initGui();

    //Clears the GUI elements and reinitializes the GUI.
    //@return void
    void resetGui();

public:

//Constructirs and Destructor:

    SettingsState(StateData* state_data);
    virtual ~SettingsState();

//Accessors:



//Fucntions:

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

