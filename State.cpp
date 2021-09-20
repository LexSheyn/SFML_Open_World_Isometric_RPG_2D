#include "stdafx.h"
#include "State.h"

//StateData class ====================================================================================================

//Constructors and Distructors:

//StateData::StateData()
//{
//
//}


//State class ====================================================================================================

//protected: Functions:

//Should use '\\' instead of '/' in the file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
void State::initKeybinds(const std::string& file_path)
{
	std::ifstream in;

	in.open(file_path);

	if (in.fail())
	{
		std::cout << "ERROR::EditorState::initKeybinds::Failed to load: " << file_path << std::endl;
	}
	else if (in.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (in >> action >> key)
		{
			this->keybinds[action] = this->supportedKeys->at(key);
		}
	}

	in.close();
}

//Should use '../' before the file path to be able to play the game without Visual Studio.
void State::initFont(sf::Font& font, const std::string& file_path)
{
	if (!font.loadFromFile(file_path))
	{
		std::cout << "ERROR::EditorState::initFont::Failed to load: " << file_path << std::endl;
	}
}

//Should use '../' before the file path to be able to play the game without Visual Studio.
void State::initTexture(const int& index, const std::string& file_path)
{
	if (!this->textures[index].loadFromFile(file_path))
	{
		std::cout << "ERROR::GameState::initTextures::Failed to load: " << file_path << std::endl;
	}
}

//Debug function.
//Initializes mouse position text.
void State::initMousePositionText()
{
	//X
	this->mousePositionTextX.setFont(this->systemFont);
	this->mousePositionTextX.setCharacterSize(gui::calculateCharSize(3.3f, this->stateData->gfxSettings->resolution));

	//Y
	this->mousePositionTextY.setFont(this->systemFont);
	this->mousePositionTextY.setCharacterSize(gui::calculateCharSize(3.3f, this->stateData->gfxSettings->resolution));
}

void State::initFpsCounter()
{
	// FPS counter
	this->fpsCounterText.setFont(this->systemFont);
	this->fpsCounterText.setCharacterSize(gui::calculateCharSize(3.3f, this->stateData->gfxSettings->resolution));
	this->fpsCounterText.setPosition
	(
		gui::percentIntoX(93.f, this->stateData->gfxSettings->resolution),
		gui::percentIntoY(2.f, this->stateData->gfxSettings->resolution)
	);
}

//Constructors and Destructor:

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 30.f;
	this->gridSize = state_data->gridSize;

	this->initFont(this->systemFont, "Fonts/PixellettersFull.ttf");

	this->initMousePositionText();
	this->initFpsCounter();
}

State::~State()
{
	
}

//Accessors:

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const bool State::getKeytime(const float max_keytime)
{
	if (this->keytime >= max_keytime)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//Functions:

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

//Debug function.
//Updating mouse position text.
void State::updateMousePositionText()
{
	//X
	this->mousePositionTextX.setPosition(this->mousePositionView.x + 20.f, this->mousePositionView.y - 24.f);
	std::stringstream ssX;
	ssX << "x: " << this->mousePositionView.x;
	this->mousePositionTextX.setString(ssX.str());

	//Y
	this->mousePositionTextY.setPosition(this->mousePositionView.x + 70.f, this->mousePositionView.y - 24.f);
	std::stringstream ssY;
	ssY << "y: " << this->mousePositionView.y;
	this->mousePositionTextY.setString(ssY.str());
}

void State::updateFpsCounter(const float& dt)
{
	this->fpsCounterText.setString("FPS: " + std::to_string(static_cast<int>(1.f / dt)));
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if (view)
	{
		this->window->setView(*view);
	}

	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePositionGrid = sf::Vector2i
	(
		static_cast<int>(this->mousePositionView.x / this->gridSize),
		static_cast<int>(this->mousePositionView.y / this->gridSize)
	);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}

//Debug function.
//Rendering mouse position text.
void State::renderMousePositionText(sf::RenderTarget* target)
{
	target->draw(this->mousePositionTextX);
	target->draw(this->mousePositionTextY);
}

void State::renderFpsCounter(sf::RenderTarget* target)
{
	target->draw(this->fpsCounterText);
}
