#pragma once

enum class ItemTypes
{
	Default = 0,
	Ranged_Weapon,
	Melee_Weapon,
	Armour
};

enum class Rarities
{
	Common = 0,
	Uncommon,
	Rare,
	Epic,
	Legendary,
	Mythic
};

class Item
{
private:

//private: Functions:

	void initVariables();

protected:

//Variables:

	ItemTypes type;
	Rarities rarity;
	int level;
	int value;
//	float weight;

public:

//Constructors and Destructor:

	Item(const int level, const int value);
	virtual ~Item();

//Functions:

	virtual Item* clone() = 0;
};

