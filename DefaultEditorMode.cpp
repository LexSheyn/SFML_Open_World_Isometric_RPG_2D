#include "stdafx.h"
#include "DefaultEditorMode.h"

//private: Functions:

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect
	(
		0,
		0,
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);

	this->collision = false;
	this->type = static_cast<int>(TileTypes::Default);
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
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

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	//Texture selector
	this->textureSelector = new gui::TextureSelector
	(
		10.f, 20.f, this->stateData->gridSize * 10.f, this->stateData->gridSize * 10.f,
		this->stateData->gridSize,
		this->tileMap->getTileSheet(),
		*this->editorStateData->font, "TS"
	);

	//Buttons

}


//Constructors and Destructor:

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	//Deleting texture selector
	delete this->textureSelector;
}


//Functions:

void DefaultEditorMode::updateInput(const float& dt)
{
	//Adding a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
		{
			if (!this->textureSelector->isActive())
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->tileEmpty(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer()))
					{
						this->tileMap->addTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer(), this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->tileMap->addTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer(), this->textureRect, this->collision, this->type);
				}
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}//Removing a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePositionWindow)))
		{
			if (!this->textureSelector->isActive())
			{
				this->tileMap->removeTile(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->tileMap->getLayer());
			}
			else
			{

			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("COLLISION_TOGGLE"))) && this->getKeytime())
	{
		if (this->collision)
		{
			this->collision = false;
		}
		else
		{
			this->collision = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_INCREASE"))) && this->getKeytime())
	{
		if (this->type < static_cast<int>(TileTypes::Doodad))
		{
			++this->type;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_DECREASE"))) && this->getKeytime())
	{
		if (this->type > static_cast<int>(TileTypes::Default))
		{
			--this->type;
		}
	}

	//Setting lock ON/OFF
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TILE_LOCK_TOGGLE"))) && this->getKeytime())
	{
		if (this->tileAddLock)
		{
			this->tileAddLock = false;
		}
		else
		{
			this->tileAddLock = true;
		}
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	//Texture selector
	this->textureSelector->update(*this->editorStateData->mousePositionWindow, dt);

	//Tile selector
	if (!this->textureSelector->isActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition
		(
			this->editorStateData->mousePositionGrid->x * this->stateData->gridSize,
			this->editorStateData->mousePositionGrid->y * this->stateData->gridSize
		);
	}

	//Cursor text
	this->cursorText.setPosition
	(
		this->editorStateData->mousePositionView->x + 100.f, 
		this->editorStateData->mousePositionView->y - 100.f
	);
	std::stringstream ss;
	ss << this->editorStateData->mousePositionView->x << "    " << this->editorStateData->mousePositionView->y
		<< std::endl << this->editorStateData->mousePositionGrid->x << "    " << this->editorStateData->mousePositionGrid->y << "    " << this->tileMap->getLayer()
		<< std::endl << this->textureRect.left << "    " << this->textureRect.top
		<< std::endl << "Collision: " << this->collision
		<< std::endl << "Type: " << this->type
		<< std::endl << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePositionGrid->x, this->editorStateData->mousePositionGrid->y, this->layer)
		<< std::endl << "Tile lock: " << this->tileAddLock;
	this->cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
	//Tile selector
	if (!this->textureSelector->isActive())
	{
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}

	//Texture selector
	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);
	//Sidebar
	target.draw(this->sideBar);

	//Cursor text
	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
