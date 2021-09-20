#include "stdafx.h"
#include "CharacterTab.h"



// Constructors and Destructor:

CharacterTab::CharacterTab(sf::VideoMode& video_mode, sf::Font& font, Player& player)
	: Tab(video_mode, font, player, false)
{
	// Background
	this->back.setSize(sf::Vector2f(gui::percentIntoX(30.f, this->videoMode), static_cast<float>(videoMode.height)));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));

	// Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText.setFillColor(sf::Color::White);
	this->infoText.setString("Character tab text");
	this->infoText.setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(2.f, this->videoMode)
	);
}

CharacterTab::~CharacterTab()
{

}


// Functions:

void CharacterTab::update(const float& dt)
{
	if (this->opened)
	{
	//	this->infoText.setString("TEST :" + std::to_string(dt));
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (this->opened)
	{
		target.draw(this->back);
		target.draw(this->infoText);
	}
}