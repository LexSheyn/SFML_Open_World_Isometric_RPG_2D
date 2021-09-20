#pragma once

#include "Tab.h"

class CharacterTab :
	public Tab
{
private:

	sf::RectangleShape back;
	sf::Text infoText;

public:

// Constructors and Destructor:

	CharacterTab(sf::VideoMode& video_mode, sf::Font& font, Player& player);
	virtual ~CharacterTab();

// Functions:

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

