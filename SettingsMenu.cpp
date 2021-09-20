#include "stdafx.h"
#include "SettingsMenu.h"

//Constructors and Destructor:

SettingsMenu::SettingsMenu(sf::VideoMode& video_mode, sf::Font& font)
	: Menu(video_mode, font)
{
	this->menuText.setString("PAUSED");
	this->menuText.setPosition
	(
		(this->container.getPosition().x + (this->container.getSize().x / 2.f)) - (this->menuText.getGlobalBounds().width / 2.f),
		this->container.getPosition().y + (this->menuText.getGlobalBounds().height * 2.f)
	);
}

SettingsMenu::~SettingsMenu()
{

}


//Accessors:




//Functions:

void SettingsMenu::update(const sf::Vector2i& mouse_position, const float& dt)
{
	//Updating buttons
	for (auto& i : this->buttons)
	{
		i.second->update(mouse_position, false, true);
		i.second->updateButtonColor(dt);
	}
}

void SettingsMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	target.draw(this->container);

	target.draw(this->menuText);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}