#pragma once

#include "Tab.h"

enum class Info
{
	Level = 0,
	Experience,
	Strength,
	Dexterity,
	Intelligence
};

class CharacterTab :
	public Tab
{
private:

// Variables:

	sf::RectangleShape back;
	std::map<const Info, sf::Text> infoText;
	std::map<const Info, std::string> infoTextString;
	std::string stringDivider;

// private: Functions:

	void initText();

public:

// Constructors and Destructor:

	CharacterTab(sf::VideoMode& video_mode, sf::Font& font, Player& player);
	virtual ~CharacterTab();

// Functions:

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

