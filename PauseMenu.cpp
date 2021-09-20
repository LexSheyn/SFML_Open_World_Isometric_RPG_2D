#include "stdafx.h"
#include "PauseMenu.h"

//Constructors and Destructor:

PauseMenu::PauseMenu(sf::VideoMode& video_mode, sf::Font& font)
	: Menu(video_mode, font)
{
//	this->menuText.setString("PAUSED");
	this->menuText.setPosition
	(
		(this->container.getPosition().x + (this->container.getSize().x / 2.f)) - (this->menuText.getGlobalBounds().width / 2.f),
		this->container.getPosition().y + (this->menuText.getGlobalBounds().height * 2.f)
	);
}

PauseMenu::~PauseMenu()
{

}


//Accessors:




//Functions:

void PauseMenu::update(const sf::Vector2i& mouse_position, const float& dt)
{
	//Updating buttons
	for (auto& i : this->buttons)
	{
		i.second->update(mouse_position, false, true);
		i.second->updateButtonColor(dt);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	target.draw(this->container);

	target.draw(this->menuText);

	target.draw(this->logoSprite);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}
