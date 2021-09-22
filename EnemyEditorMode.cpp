#include "stdafx.h"
#include "EnemyEditorMode.h"

//private: Functions:

void EnemyEditorMode::initVariables()
{
	this->type = 0;
	this->amount = 10;
	this->timeToSpawn = 1;
	this->distanceMax = 1000.f;
}

void EnemyEditorMode::initGui()
{
	//Cursor text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(18);
	this->cursorText.setPosition(this->editorStateData->mousePositionView->x + 100.f, this->editorStateData->mousePositionView->y - 50.f);

	//Sidebar
	this->sideBar.setSize(sf::Vector2f(this->stateData->gridSize, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(-1.f);

	//Tile selector
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}


//Constructors and Destructor:

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{

}


//Functions:

void EnemyEditorMode::updateInput(const float& dt)
{
	//Adding a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->getKeyTime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
		{
			this->tileMap->addTile
			(
				this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer(), this->iR, 
				this->type, this->amount, this->timeToSpawn, this->distanceMax);
		}
	}//Removing a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && this->getKeyTime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
		{
			this->tileMap->removeTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer(), static_cast<int>(TileTypes::EnemySpawner));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			if (this->type > 0)
			{
				--this->type;
			}			
		}
		else
		{
			if (this->type < 100)
			{
				++this->type;
			}			
		}		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("AMOUNT_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			--this->amount;
		}
		else
		{
			++this->amount;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TIME_TO_SPAWN_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			--this->timeToSpawn;
		}
		else
		{
			++this->timeToSpawn;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("DISTANCE_MAX_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			--this->distanceMax;
		}
		else
		{
			++this->distanceMax;
		}
	}
}

void EnemyEditorMode::updateGui(const float& dt)
{
	//Selector rectangle
	this->selectorRect.setPosition
	(
		this->editorStateData->mousePositionGrid->x * this->stateData->gridSize,
		this->editorStateData->mousePositionGrid->y * this->stateData->gridSize
	);

	//Cursor text
	this->cursorText.setPosition
	(
		this->editorStateData->mousePositionView->x + 100.f, 
		this->editorStateData->mousePositionView->y - 100.f
	);
	std::stringstream ss;
	ss << this->editorStateData->mousePositionView->x << "    " << this->editorStateData->mousePositionView->y
		<< std::endl << this->editorStateData->mousePositionGrid->x << "    " << this->editorStateData->mousePositionGrid->y << "    " << this->tileMap->getLayer()
		<< std::endl << this->iR.left << "    " << this->iR.top
		<< std::endl << "Type: " << this->type
		<< std::endl << "Amount: " << this->amount
		<< std::endl << "Time to spawn: " << this->timeToSpawn
		<< std::endl << "Max distance: " << this->distanceMax
		<< std::endl << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer())
		<< std::endl << "Tile lock: " << "";
	this->cursorText.setString(ss.str());
}

void EnemyEditorMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
	//Selector rectangle
	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorText);

	//Side bar
	target.setView(this->stateData->window->getDefaultView());
	target.draw(this->sideBar);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
