#include "stdafx.h"
#include "PlayerTabPanel.h"

// private: Functions:

void PlayerTabPanel::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}


// Constructors and Destructor:

PlayerTabPanel::PlayerTabPanel(sf::VideoMode& video_mode, sf::Font& font, Player& player)
	: videoMode(video_mode), font(font), player(player), 
	characterTab(video_mode, font, player)
{
	this->initKeyTime();

	this->buttonPressed = false;
}

PlayerTabPanel::~PlayerTabPanel()
{

}


// Accessors:

const bool PlayerTabPanel::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		
		return true;
	}

	return false;
}

const bool PlayerTabPanel::isOpen() const
{
	if (this->characterTab.isOpen())
	{
		return true;
	}

	return false;
}


// Functions:

void PlayerTabPanel::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			if (this->characterTab.isOpen())
			{
				this->characterTab.close();
			}
			else
			{
				this->characterTab.open();
			}
		}		
	}
	else
	{
		this->buttonPressed = false;
	}
}

void PlayerTabPanel::update(const float& dt)
{
	this->updateInput();
	this->characterTab.update(dt);
}

void PlayerTabPanel::render(sf::RenderTarget& target)
{
	this->characterTab.render(target);
}