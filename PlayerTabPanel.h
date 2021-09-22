#pragma once

#include "CharacterTab.h"

class PlayerTabPanel
{
private:

// Core:

	sf::VideoMode& videoMode;
	sf::Font& font;
	Player& player;
	bool buttonPressed;

	sf::Clock keyTimer;
	float keyTimeMax;

// Character tab:

	CharacterTab characterTab;

// private: Functions:

	void initKeyTime();

public:

// Constructors and Destructor:

	PlayerTabPanel(sf::VideoMode& video_mode, sf::Font& font, Player& player);
	virtual ~PlayerTabPanel();

// Accessors:

	const bool getKeyTime();
	const bool isOpen() const;

// Functions:

	void toggleCharacterTab();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

