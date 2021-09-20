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

const bool EditorMode::getKeytime()
{
	if (*this->editorStateData->keytime >= *this->editorStateData->keytimeMax)
	{
		*this->editorStateData->keytime = 0.f;
		return true;
	}

	return false;
}

const bool EditorMode::getKeytime(const float max_keytime)
{
	if (*this->editorStateData->keytime >= max_keytime)
	{
		*this->editorStateData->keytime = 0.f;
		return true;
	}

	return false;
}
