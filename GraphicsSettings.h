#pragma once

class GraphicsSettings
{
public:

// Constructors and Destructor: // Default Distructor

	GraphicsSettings();

// Variables:

	std::string title;
	sf::VideoMode resolution;
	unsigned short fullscreen;
	sf::Uint32 style;
	unsigned frameRateLimit;
	bool verticalSync;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

// Fucntions:

	//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
	//to be able to play the game without Visual Studio.
	void saveToFile(const std::string file_path);

	//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
	//to be able to play the game without Visual Studio.
	void loadFromFile(const std::string file_path);
};