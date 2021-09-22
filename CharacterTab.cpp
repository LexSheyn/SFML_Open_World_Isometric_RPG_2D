#include "stdafx.h"
#include "CharacterTab.h"

// private: Functions:

void CharacterTab::initText()
{
	// String divider
	this->stringDivider = ": ";

	// Level
	this->infoTextString[Info::Level] = "Level";
	this->infoText[Info::Level].setFont(this->font);
	this->infoText[Info::Level].setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText[Info::Level].setFillColor(sf::Color::White);	
	this->infoText[Info::Level].setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(2.f, this->videoMode)
	);
	this->infoText[Info::Level].setString(this->infoTextString[Info::Level]);

	// Experience
	this->infoTextString[Info::Experience] = "Experience";
	this->infoText[Info::Experience].setFont(this->font);
	this->infoText[Info::Experience].setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText[Info::Experience].setFillColor(sf::Color::White);
	this->infoText[Info::Experience].setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(6.f, this->videoMode)
	);
	this->infoText[Info::Experience].setString(this->infoTextString[Info::Experience]);

	// Strength
	this->infoTextString[Info::Strength] = "Strength";
	this->infoText[Info::Strength].setFont(this->font);
	this->infoText[Info::Strength].setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText[Info::Strength].setFillColor(sf::Color::White);
	this->infoText[Info::Strength].setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(20.f, this->videoMode)
	);
	this->infoText[Info::Strength].setString(this->infoTextString[Info::Strength]);

	// Dexterity
	this->infoTextString[Info::Dexterity] = "Dexterity";
	this->infoText[Info::Dexterity].setFont(this->font);
	this->infoText[Info::Dexterity].setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText[Info::Dexterity].setFillColor(sf::Color::White);
	this->infoText[Info::Dexterity].setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(24.f, this->videoMode)
	);
	this->infoText[Info::Dexterity].setString(this->infoTextString[Info::Dexterity]);

	// Intelligence
	this->infoTextString[Info::Intelligence] = "Intelligence";
	this->infoText[Info::Intelligence].setFont(this->font);
	this->infoText[Info::Intelligence].setCharacterSize(gui::calculateCharSize(3.f, this->videoMode));
	this->infoText[Info::Intelligence].setFillColor(sf::Color::White);
	this->infoText[Info::Intelligence].setPosition
	(
		this->back.getPosition().x + gui::percentIntoX(2.f, this->videoMode),
		this->back.getPosition().y + gui::percentIntoY(28.f, this->videoMode)
	);
	this->infoText[Info::Intelligence].setString(this->infoTextString[Info::Intelligence]);
}


// Constructors and Destructor:

CharacterTab::CharacterTab(sf::VideoMode& video_mode, sf::Font& font, Player& player)
	: Tab(video_mode, font, player, false)
{
	// Background
	this->back.setSize(sf::Vector2f(gui::percentIntoX(30.f, this->videoMode), static_cast<float>(videoMode.height)));
	this->back.setFillColor(sf::Color(0, 40, 80, 240));

	// Text
	this->initText();
}

CharacterTab::~CharacterTab()
{

}


// Functions:

void CharacterTab::update(const float& dt)
{
	if (this->opened)
	{
		this->infoText[Info::Level].setString(this->infoTextString[Info::Level] + this->stringDivider + std::to_string(this->player.getAttributeComponent()->level));

		this->infoText[Info::Experience].setString(this->infoTextString[Info::Experience] + this->stringDivider + std::to_string(this->player.getAttributeComponent()->exp));

		this->infoText[Info::Strength].setString(this->infoTextString[Info::Strength] + this->stringDivider + std::to_string(this->player.getAttributeComponent()->strength));

		this->infoText[Info::Dexterity].setString(this->infoTextString[Info::Dexterity] + this->stringDivider + std::to_string(this->player.getAttributeComponent()->dexterity));

		this->infoText[Info::Intelligence].setString(this->infoTextString[Info::Intelligence] + this->stringDivider + std::to_string(this->player.getAttributeComponent()->intelligence));
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (this->opened)
	{
		target.draw(this->back);
		
		for (auto& text : this->infoText)
		{
			target.draw(text.second);
		}
	//	target.draw(this->infoText);
	}
}