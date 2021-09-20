#include "stdafx.h"
#include "Menu.h"


// protected: Functions:

void Menu::initTexture(sf::Texture& texture, const std::string file_path)
{
	if (!texture.loadFromFile(file_path))
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::initTexture::Failed to load" << file_path << std::endl;
	}
}


// Constructors and Destructor:

Menu::Menu(sf::VideoMode& video_mode, sf::Font& font)
	: font(font)
{
	//Background initialization
	this->background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(video_mode.width),
			static_cast<float>(video_mode.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Container initialization
	this->container.setSize
	(
		sf::Vector2f
		(
		//	static_cast<float>(video_mode.width) / 4.f,
			static_cast<float>(video_mode.width) / 3.f,
		//	static_cast<float>(video_mode.height) / 1.2f
			static_cast<float>(video_mode.height)
		)
	);
	this->container.setFillColor(sf::Color(0, 40, 80, 80));
	this->container.setPosition
	(
	//	(static_cast<float>(video_mode.width) / 2.f) - (this->container.getSize().x / 2.f),
	//	(static_cast<float>(video_mode.height) / 2.f) - (this->container.getSize().y / 2.f)
		0.f, 0.f
	);

	// Text initialization
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(100, 100, 100, 200));
	this->menuText.setCharacterSize(gui::calculateCharSize(4.f, video_mode));
//	this->menuText.setString("MENU");
	this->menuText.setPosition
	(
		(this->container.getPosition().x + (this->container.getSize().x / 2.f)) - (this->menuText.getGlobalBounds().width / 2.f),
		this->container.getPosition().y + (this->menuText.getGlobalBounds().height * 2.f)
	);

	// Logo
	this->initTexture(this->logoTexture, "D:/PNG/Logo/128x128_2.png");
	this->logoSprite.setTexture(this->logoTexture);
//	this->logoSprite.setScale(1.f, 1.f);
	this->logoSprite.setPosition
	(
		(this->container.getPosition().x + (this->container.getSize().x / 2.f)) - (this->logoSprite.getGlobalBounds().width / 2.f),
		this->container.getPosition().y + (this->logoSprite.getGlobalBounds().height / 4.f)
	);
}

Menu::~Menu()
{
	// Deleting buttons
	//auto it = this->buttons.begin();
	std::map<const gui::ButtonName, gui::Button*>::iterator it;
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


//Accessors:

std::map<const gui::ButtonName, gui::Button*>& Menu::getButtons()
{
	return this->buttons;
}

//Functions:

const bool Menu::isButtonPressed(const gui::ButtonName name)
{
	return this->buttons[name]->isPressed();
}

void Menu::addButton
(
	const gui::ButtonName name,
	const float y,
	const float width,
	const float height,
	const unsigned char_size,
	const std::string text
)
{
	float x = (this->container.getPosition().x + (this->container.getSize().x / 2.f)) - (width / 2.f);

	this->buttons[name] = new gui::Button
	(
		x, y, width, height,
		&this->font, text, char_size,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);
}