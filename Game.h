#pragma once

#include "MainMenuState.h"

class Game
{
private:

	//Variables:

	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//private: Static functions:


	//private: Initialization functions:

	void initVariables();
	void initGraphicsSettings(const std::string file_path);
	void initWindow();	
	void initKeys(const std::string file_path);
	void initStateData();
	void initStates();

public:

//Constructors and Destructor:

	Game();
	virtual ~Game();

//Accessors:


//Modifiers:


//Functions:

	//Regular:

	void endApplication();

	//Update:

	void updateDt();
	void updateEventsSFML();
	void update();

	//Render:

	void render();

	//Core:
	
	void run();
};

