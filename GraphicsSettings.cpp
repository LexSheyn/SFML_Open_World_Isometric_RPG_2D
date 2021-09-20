#include "stdafx.h"
#include "GraphicsSettings.h"

//Constructors and Destructor: //No Distructor

GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = 0; // 0 - Titlebar | Close, 1 - Fullscreen, 2 - None , else - Default
	this->style = sf::Style::Titlebar | sf::Style::Close;
	this->frameRateLimit = 120;
	this->verticalSync = false;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Fucntions:

//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
void GraphicsSettings::saveToFile(const std::string file_path)
{
	std::ofstream out;

	out.open(file_path);

	if (out.is_open())
	{
		out << this->title << "\n";
		out << this->resolution.width << " " << this->resolution.height << "\n";
		out << this->fullscreen << "\n";
		out << this->frameRateLimit << "\n";
		out << this->verticalSync << "\n";
		out << this->contextSettings.antialiasingLevel << "\n";
	}

	out.close();
}

//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
void GraphicsSettings::loadFromFile(const std::string file_path)
{
	std::ifstream in;

	in.open(file_path);

	if (in.fail())
	{
		std::cout << "ERROR::GraphicsSettings::loadFromFile::Failed to load: " << file_path << std::endl;
	}
	else if (in.is_open())
	{
		std::getline(in, title);
		in >> this->resolution.width >> this->resolution.height;
		in >> this->fullscreen;
		in >> this->frameRateLimit;
		in >> this->verticalSync;
		in >> this->contextSettings.antialiasingLevel;
	}

	in.close();

	if (this->fullscreen == 0)
	{
		this->style = sf::Style::Titlebar | sf::Style::Close;
	}
	else if (this->fullscreen == 1)
	{
		this->style = sf::Style::Fullscreen;
	}
	else if (this->fullscreen == 2)
	{
		this->style = sf::Style::None;
	}
	else
	{
		this->style = sf::Style::Default;
	}
}