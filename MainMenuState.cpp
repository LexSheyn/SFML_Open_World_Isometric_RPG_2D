#include "stdafx.h"
#include "MainMenuState.h"

//private: Functions:

void MainMenuState::initVariables()
{

}

//Should use '../' before the file path to be able to play the game without Visual Studio.
void MainMenuState::initBackground(const std::string file_path)
{
	sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	//Background initialization
	this->background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile(file_path))
	{
		std::cout << "ERROR::SettingsState::initBackground::Failed to load: " << file_path << std::endl;
		this->background.setFillColor(sf::Color(30, 60, 60, 200));
	}
	else
	{
		this->background.setTexture(&this->backgroundTexture);
	}

	//Container initialization
//	this->container.setSize(sf::Vector2f(gui::percentIntoX(22.f, vm), gui::percentIntoY(56.f, vm)));
//	this->container.setFillColor(sf::Color(0, 40, 80, 80));
//	this->container.setPosition(sf::Vector2f(gui::percentIntoX(8.f, vm), gui::percentIntoY(12.f, vm)));

	this->container.setPosition(0.f, gui::percentIntoY(70.f, vm));
	this->container.setFillColor(sf::Color(0, 40, 80, 80));
	this->container.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height) / 9.f
		)
	);
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->initBackground("Resources/Images/Backgrounds/background_1280x720.png");

	//Buttons
	this->buttons["GAME_STATE"] = new gui::Button
	(
		gui::percentIntoX(12.f, vm), gui::percentIntoY(73.f, vm), 
		gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Start", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button
	(
		gui::percentIntoX(32.f, vm), gui::percentIntoY(73.f, vm),
		gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Settings", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button
	(
		gui::percentIntoX(52.f, vm), gui::percentIntoY(73.f, vm),
		gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Editor", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button
	(
		gui::percentIntoX(72.f, vm), gui::percentIntoY(73.f, vm),
		gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Exit", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);
}

//Clears the GUI elements and reinitializes the GUI.
//@return void
void MainMenuState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

//Constructors and Destructor:

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{	
	this->initVariables();

//	std::thread t2(&MainMenuState::initFont, this, std::ref(this->font), "Fonts/aAtmospheric.ttf");
//	std::thread t3(&MainMenuState::initFont, this, std::ref(this->systemFont), "Fonts/Dosis-Light.ttf");
//	std::thread t4(&MainMenuState::initKeybinds, this, "Config/mainmenustate_keybinds.ini");
		
	this->initFont(this->font ,"Fonts/slkscr.ttf");
//	this->initFont(this->systemFont ,"Fonts/Dosis-Light.ttf");
	this->initKeybinds("Config/mainmenustate_keybinds.ini");

//	t2.join();
//	t3.join();
//	t4.join();

	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
	//Deleting buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions:

void MainMenuState::updateInput(const float& dt)
{

}

//Updates all the buttons in the state and handles theis functionality.
void MainMenuState::updateButtons(const float& dt)
{	
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow, false, true);
		it.second->updateButtonColor(dt);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed() && this->getKeytime())
	{
		//Game
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed() && this->getKeytime())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed() && this->getKeytime())
	{
		//Editor
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed() && this->getKeytime())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateButtons(dt);

//Debug:

	this->updateFpsCounter(dt);
//	this->updateMousePositionText();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->container);

	this->renderButtons(*target);

//Debug:

	this->renderFpsCounter(target);
//	this->renderMousePositionText(target);
}