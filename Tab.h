#pragma once

#include "Player.h"

class Tab
{
protected:

	sf::VideoMode& videoMode;
	sf::Font& font;
	Player& player;
	bool opened;

public:

// Constructors and Destructor:

	Tab(sf::VideoMode& video_mode, sf::Font& font, Player& player, const bool opened);
	virtual ~Tab();

// Accessors:

	const bool& isOpen() const;

// Functions:

	void open();
	void close();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

