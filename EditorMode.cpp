#include "stdafx.h"
#include "EditorMode.h"

//Constructors and Destructor:

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data)
{

}

EditorMode::~EditorMode()
{

}

//Accessors:

const bool EditorMode::getKeyTime()
{
	if (this->editorStateData->keyTimer->getElapsedTime().asSeconds() >= *this->editorStateData->keyTimeMax)
	{
		this->editorStateData->keyTimer->restart();

		return true;
	}

	return false;
}

const bool EditorMode::getKeyTime(const float key_time_max)
{
	if (this->editorStateData->keyTimer->getElapsedTime().asSeconds() >= key_time_max)
	{
		this->editorStateData->keyTimer->restart();

		return true;
	}

	return false;
}
