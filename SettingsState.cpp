#include "stdafx.h"
#include "SettingsState.h"

//private: Functions:

void SettingsState::initVariables()
{
//	this->modes = sf::VideoMode::getFullscreenModes();
	this->modes.push_back(sf::VideoMode(1920, 1080));
	this->modes.push_back(sf::VideoMode(1904, 1071));
	this->modes.push_back(sf::VideoMode(1600, 900));
	this->modes.push_back(sf::VideoMode(1584, 891));
	this->modes.push_back(sf::VideoMode(1280, 720));
	this->modes.push_back(sf::VideoMode(1264, 711));
}

//Should use '../' before the file path to be able to play the game without Visual Studio.
void SettingsState::initBackground(const std::string file_path)
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
	this->container.setSize(sf::Vector2f(gui::percentIntoX(44.f, vm), gui::percentIntoY(56.f, vm)));
	this->container.setFillColor(sf::Color(0, 40, 80, 140));
	this->container.setPosition(sf::Vector2f(gui::percentIntoX(30.f, vm), gui::percentIntoY(12.f, vm)));
}

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->initBackground("Resources/Images/Backgrounds/background_1280x720.png");

	//Buttons
	this->buttons["APPLY"] = new gui::Button
	(
		gui::percentIntoX(50.f, vm), gui::percentIntoY(60.f, vm), gui::percentIntoX(9.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Apply", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button
	(
		gui::percentIntoX(62.f, vm), gui::percentIntoY(60.f, vm), gui::percentIntoX(9.f, vm), gui::percentIntoY(4.f, vm),
		&this->font, "Back", gui::calculateCharSize(3.f, vm),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(204, 204, 204), sf::Color(255, 235, 0), sf::Color(255, 100, 0)
	);

	//Modes
	std::vector<std::string> modes_str;

	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
	}

	//Dropdown list
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList
	(
		gui::percentIntoX(55.f, vm), gui::percentIntoY(15.f, vm),
		gui::percentIntoX(12.f, vm), gui::percentIntoY(3.5f, vm),
		this->stateData->gfxSettings->resolution,
		this->settingsFont, gui::calculateCharSize(2.625f, vm), 
		modes_str.data(), static_cast<unsigned>(modes_str.size())
	);

	//Text
	for (int32_t i = 0; i < 4; i++)
	{
		this->optionsText[i].setFont(this->font);
		this->optionsText[i].setPosition(sf::Vector2f(gui::percentIntoX(33.f, vm), gui::percentIntoY(15.f, vm) + (gui::calculateCharSize(6.f, vm) * static_cast<float>(i))));
		this->optionsText[i].setCharacterSize(gui::calculateCharSize(3.f, vm));
		this->optionsText[i].setFillColor(sf::Color(255, 255, 255));
	}

	this->optionsText[0].setString("Resolution");
	this->optionsText[1].setString("Fullscreen");
	this->optionsText[2].setString("Framerate");
	this->optionsText[3].setString("Anti-aliasing");
}

//Clears the GUI elements and reinitializes the GUI.
//@return void
void SettingsState::resetGui()
{
	auto it_1 = this->buttons.begin();
	for (it_1 = this->buttons.begin(); it_1 != this->buttons.end(); ++it_1)
	{
		delete it_1->second;
	}
	this->buttons.clear();

	auto it_2 = this->dropDownLists.begin();
	for (it_2 = this->dropDownLists.begin(); it_2 != this->dropDownLists.end(); ++it_2)
	{
		delete it_2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
	this->initFpsCounter();
}

//Constructors and Destructor:

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
		
	this->initFont(this->font, "Fonts/slkscr.ttf");
	this->initFont(this->settingsFont, "Fonts/slkscr.ttf");
	this->initKeybinds("Config/mainmenustate_keybinds.ini");
	this->initGui();
}

SettingsState::~SettingsState()
{
	//Deleting buttons
	auto it_i = this->buttons.begin();
	for (it_i = this->buttons.begin(); it_i != this->buttons.end(); ++it_i)
	{
		delete it_i->second;
	}

	//Deleting drowdown lists
	auto it_j = this->dropDownLists.begin();
	for (it_j = this->dropDownLists.begin(); it_j != this->dropDownLists.end(); ++it_j)
	{
		delete it_j->second;
	}
}

//Accessors:



//Functions:

void SettingsState::updateInput(const float& dt)
{

}

//Updates all GUI elements in the state and handles theis functionality.
void SettingsState::updateGui(const float& dt)
{
	//Updating buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow, false, true);
		it.second->updateButtonColor(dt);
	}

//Buttons functionality:

	//Back to the main menu
	if (this->buttons["EXIT_STATE"]->isPressed() && this->getKeytime())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed() && this->getKeytime())
	{
		//TEST, REMOVE LATER
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create
		(
			this->stateData->gfxSettings->resolution, 
			this->stateData->gfxSettings->title, 
			this->stateData->gfxSettings->style,
			this->stateData->gfxSettings->contextSettings
		);
		this->window->setFramerateLimit(this->stateData->gfxSettings->frameRateLimit);
		this->window->setVerticalSyncEnabled(this->stateData->gfxSettings->verticalSync);
		//this->window->setMouseCursorGrabbed(true);

		this->resetGui();
	}


	//Updating dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePositionWindow, dt);
	}

//Dropdown lists functionality:


}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateGui(dt);

//Debug:

	this->updateFpsCounter(dt);
//	this->updateMousePositionText();
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	//Whole state
	if (!target)
	{
		target = this->window;
	}

	//Background
	target->draw(this->background);
	target->draw(this->container);

	//GUI
	this->renderGui(*target);

	//Options text
	for (int32_t i = 0; i < 4; i++)
	{
		target->draw(this->optionsText[i]);
	}	

//Debug:

	this->renderFpsCounter(target);
//	this->renderMousePositionText(target);
}