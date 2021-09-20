#include "stdafx.h"
#include "Item.h"

//private: Functions:

void Item::initVariables()
{

}


//Constructors and Destructors:

Item::Item(const int level, const int value)
{
	this->initVariables();

	this->level = level;
	this->value = value;
	this->type = ItemTypes::Default;
}

Item::~Item()
{

}