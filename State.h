#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

//enum MOUSE_POSITION_STATES
//{
//	MOUSE_SCREEN = 1,
//	MOUSE_WINDOW,
//	MOUSE_VIEW
//};

class State;

class StateData
{
public:

//Constructors and Distructor: //No distructor

//	StateData() {};

//Variables:

	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected:

	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2i mousePositionGrid;

	sf::Font systemFont;

	sf::Text mousePositionTextX;
	sf::Text mousePositionTextY;
	
	sf::Text fpsCounterText;

//Resources:

	std::map<const int, sf::Texture> textures;

	//TEST TEXTURES
	std::map<const int, std::map<const int, sf::Texture>> playerTextures;
	std::map<const int, std::map<const int, sf::Texture>> enemyTextures;
	std::map<const int, std::map<const int, sf::Texture>> bossTextures;

	/*
	//EXAMPLE:

	playerTextures[Players::PlayerOne][TextureSheets::Idle] = sf::Texture();
	playerTextures[Players::PlayerOne][TextureSheets::Move] = sf::Texture();

	enemyTextures[Enemies::Rat][TextureSheets::Idle] = sf::Texture();
	enemyTextures[Enemies::Rat][TextureSheets::Move] = sf::Texture();

	bossTextures[Enemies::Fly][TextureSheets::Idle] = sf::Texture();
	bossTextures[Enemies::Fly][TextureSheets::Move] = sf::Texture();
	*/

// Sound engine:

	sfx::SoundEngine soundEngine;

// protected: Functions

	// Should use '\\' instead of '/' in the file path and put this file to the .exe location,
	// to be able to play the game without Visual Studio.
	void initKeybinds(const std::string& file_path);

	// Should use '../' before the file path to be able to play the game without Visual Studio.
	void initFont(sf::Font& font, const std::string& file_path);

	// Should use '../' before the file path to be able to play the game without Visual Studio.
	void initTexture(const int& index, const std::string& file_path);

// Debug:

	// Debug function.
	// Initializes mouse position text.
	void initMousePositionText();

	void initFpsCounter();

public:

// Constructors and Destructor:

	State(StateData* state_data);
	virtual ~State();

// Accessors:

	const bool& getQuit() const;
	const bool getKeytime();
	const bool getKeytime(const float max_keytime);

// Functions:

	void endState();
	void pauseState();
	void unpauseState();

	void updateMousePositionText();
	void updateFpsCounter(const float& dt);

	virtual void updateMousePositions(sf::View* view = nullptr);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;


	void renderMousePositionText(sf::RenderTarget* target);
	void renderFpsCounter(sf::RenderTarget* target);

	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

