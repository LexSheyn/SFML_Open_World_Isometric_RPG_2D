#pragma once

#include "Menu.h"

class PauseMenu : 
	public Menu
{
private:

	//

//private: Functions:

	//void initButtons();

public:

// Constructors and Destructor:

	PauseMenu(sf::VideoMode& video_mode, sf::Font& font);
	virtual ~PauseMenu();

// Accessors:

	//

// Functions:

	void update(const sf::Vector2i& mouse_position, const float& dt);
	void render(sf::RenderTarget& target);
};

