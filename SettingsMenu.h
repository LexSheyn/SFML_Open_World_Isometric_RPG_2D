#pragma once
#include "Menu.h"
class SettingsMenu :
    public Menu
{
private:

	//

//private: Functions:

	//void initButtons();

public:

	// Constructors and Destructor:

	SettingsMenu(sf::VideoMode& video_mode, sf::Font& font);
	virtual ~SettingsMenu();

	// Accessors:

		//

	// Functions:

	void update(const sf::Vector2i& mouse_position, const float& dt);
	void render(sf::RenderTarget& target);
};

