#include "stdafx.h"
#include "Tab.h"

// Constructors and Destructor:

Tab::Tab(sf::VideoMode& video_mode, sf::Font& font, Player& player, const bool opened)
	: videoMode(video_mode), font(font), player(player), opened(opened)
{
}

Tab::~Tab()
{
}


// Accessors:

const bool& Tab::isOpen() const
{
	return this->opened;
}


// Functions:

void Tab::open()
{
	this->opened = true;
}

void Tab::close()
{
	this->opened = false;
}
