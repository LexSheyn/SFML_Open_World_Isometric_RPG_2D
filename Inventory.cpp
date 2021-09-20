#include "stdafx.h"
#include "Inventory.h"

//private: Functions:

void Inventory::initialize()
{
	this->numberOfItems = 0;
	this->itemArray = new Item*[this->capacity];
	
	this->nullify();
}

void Inventory::nullify(const unsigned int from)
{
	for (size_t i = from; i < static_cast<size_t>(this->capacity); i++)
	{
		this->itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	for (size_t i = 0; i < static_cast<size_t>(this->numberOfItems); i++)
	{
		delete this->itemArray[i];
	}

	delete[] this->itemArray;
}


//Constructors and Destructor:

Inventory::Inventory(const unsigned int capacity)
{
	this->capacity = capacity;
	this->initialize();
}

Inventory::~Inventory()
{
	this->freeMemory();
}


//Accessors:

const unsigned int& Inventory::getSize() const
{
	return this->numberOfItems;
}

const unsigned int& Inventory::getSizeMax() const
{
	return this->capacity;
}

const bool Inventory::isEmpty() const
{
	return this->numberOfItems == 0;
}


//Modifiers:

	//


//Functions:

void Inventory::clearInventory()
{
	for (size_t i = 0; i < static_cast<size_t>(this->numberOfItems); i++)
	{
		delete this->itemArray[i];
	}

	this->numberOfItems = 0;

	this->nullify();
}

const bool Inventory::add(Item* item)
{
	if (this->numberOfItems < this->capacity)
	{
		this->itemArray[this->numberOfItems++] = item->clone();
		//numberOfItems will be increased after assigning it to itemArray as a number of element

		return true;
	}

	return false;
}

const bool Inventory::remove(const int index)
{
	if (this->numberOfItems > 0)
	{
		if (index < 0 || index > static_cast<int>(this->capacity))
		{
			std::cout << "ERROR::Inventory::remove::Index is out of range" << std::endl;

			return false;
		}
		else if (this->itemArray[index] != nullptr)
		{
			delete this->itemArray[index];
			this->itemArray[index] = nullptr;

			this->numberOfItems--;

			std::cout << "Inventory::remove::Item deleted from slot: " << index << std::endl;

			return true;
		}		
	}

	return false;
}

const bool Inventory::saveToFile(const std::string& file_path)
{
	return false;
}

const bool Inventory::loadFromFile(const std::string& file_path)
{
	return false;
}

void Inventory::update()
{

}

void Inventory::render()
{

}
