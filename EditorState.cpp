#include "stdafx.h"
#include "EditorState.h"

//private: Functions:

void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	
	this->editorStateData.font = &this->font;

	this->editorStateData.keybinds = &this->keybinds;
	
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;

	this->editorStateData.mousePositionScreen = &this->mousePositionScreen;
	this->editorStateData.mousePositionWindow = &this->mousePositionWindow;
	this->editorStateData.mousePositionView = &this->mousePositionView;
	this->editorStateData.mousePositionGrid = &this->mousePositionGrid;
}

void EditorState::initView()
{
	this->view.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(this->stateData->gfxSettings->resolution.width), 
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		//	1920.f,
		//	1080.f
		)
	);

	this->view.setCenter
	(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f, 
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	//	1920.f / 2.f,
	//	1080.f / 2.f
	);
}

void EditorState::initPauseMenu()
{
	const sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	this->pauseMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pauseMenu->addButton(gui::ButtonName::Resume, gui::percentIntoY(24.f, vm), gui::percentIntoX(10.f, vm), gui::percentIntoY(5.f, vm), gui::calculateCharSize(3.f, vm), "Resume");
	this->pauseMenu->addButton(gui::ButtonName::Save, gui::percentIntoY(32.f, vm), gui::percentIntoX(10.f, vm), gui::percentIntoY(5.f, vm), gui::calculateCharSize(3.f, vm), "Save");
	this->pauseMenu->addButton(gui::ButtonName::Load, gui::percentIntoY(40.f, vm), gui::percentIntoX(10.f, vm), gui::percentIntoY(5.f, vm), gui::calculateCharSize(3.f, vm), "Load");
	this->pauseMenu->addButton(gui::ButtonName::Settings, gui::percentIntoY(48.f, vm), gui::percentIntoX(10.f, vm), gui::percentIntoY(5.f, vm), gui::calculateCharSize(3.f, vm), "Settings");
	this->pauseMenu->addButton(gui::ButtonName::Quit, gui::percentIntoY(64.f, vm), gui::percentIntoX(10.f, vm), gui::percentIntoY(5.f, vm), gui::calculateCharSize(3.f, vm), "Quit");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, 1, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = static_cast<unsigned int>(EditorModes::Default);
}

//Constructors and Destructor:

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFont(this->font, "Fonts/Dosis-Light.ttf");
	this->initKeybinds("Config/editorstate_keybinds.ini");
	this->initPauseMenu();
	this->initButtons();	
	this->initTileMap();
	this->initGui();

	this->initModes();
}

EditorState::~EditorState()
{
	//Deleting buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	//Deleting pause menu
	delete this->pauseMenu;

	//Deleting tile map
	delete this->tileMap;

	//Deleting editor modes
	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

//Functions:

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Moving view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_MOVE_UP"))))
	{
		this->view.move(0.f, -std::ceil( this->cameraSpeed * dt));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_MOVE_DOWN"))))
	{
		this->view.move(0.f, std::ceil(this->cameraSpeed * dt));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_MOVE_LEFT"))))
	{
		this->view.move(-std::ceil(this->cameraSpeed * dt), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_MOVE_RIGHT"))))
	{
		this->view.move(std::ceil(this->cameraSpeed * dt), 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < static_cast<unsigned int>(this->modes.size() - 1u))
		{
			this->activeMode++;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
		}
	}
}

void EditorState::updateView(const float& dt)
{
	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

//Updates all the buttons in the state and handles theis functionality.
void EditorState::updateButtons(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow);
		it.second->updateButtonColor(dt);
	}
}

void EditorState::updateGui(const float& dt)
{
	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed(gui::ButtonName::Resume) && this->getKeytime())
	{
		this->paused = false;
	}
	else if (this->pauseMenu->isButtonPressed(gui::ButtonName::Save) && this->getKeytime())
	{
		this->tileMap->saveToFile("Maps/test.tilemap");
	}
	else if (this->pauseMenu->isButtonPressed(gui::ButtonName::Load) && this->getKeytime())
	{
		this->tileMap->loadFromFile("Maps/test.tilemap");
	}
	else if (this->pauseMenu->isButtonPressed(gui::ButtonName::Quit) && this->getKeytime())
	{
		this->endState();
	}
}

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);	

	if (!this->paused) //Unpaused update
	{
		this->updateView(dt);
		this->updateButtons(dt);
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
	}
	else //Paused update
	{
		this->pauseMenu->update(this->mousePositionWindow, dt);
		this->updatePauseMenuButtons();
	}

//Debug:

	this->updateFpsCounter(dt);
//	this->updateMousePositionText();
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}	

	//Map
	target->setView(this->view);
	this->tileMap->render(*target, this->viewGridPosition, nullptr, sf::Vector2f(), true);
	this->tileMap->renderDeffered(*target);

	//GUI
	target->setView(this->window->getDefaultView());	
	this->renderButtons(*target);
	this->renderGui(*target);
	this->renderModes(*target);

	//Pause menu
	if (this->paused) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->pauseMenu->render(*target);
	}

//Debug:

	this->renderFpsCounter(target);
//	this->renderMousePositionText(target);
}