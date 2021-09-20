#pragma once

#include "Item.h"

class Inventory
{
private:

	Item** itemArray;
	unsigned int numberOfItems;
	unsigned int capacity;

//private: Functions:

	void initialize();
	void nullify(const unsigned int from = 0);
	void freeMemory();

public:

//Constuctors and Destructor:

	Inventory(const unsigned int capacity);
	virtual ~Inventory();

//Accessors:

	const unsigned int& getSize() const;
	const unsigned int& getSizeMax() const;
	const bool isEmpty() const;

//Modifiers:

	//

//Functions:

	void clearInventory();
	
	const bool add(Item* item);
	const bool remove(const int index);

	const bool saveToFile(const std::string& file_path);
	const bool loadFromFile(const std::string& file_path);

	void update();
	void render();
};

