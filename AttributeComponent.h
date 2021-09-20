#pragma once
class AttributeComponent
{
public:

//Variables:

	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

//Constructors and Destructor:

	AttributeComponent(int level);
	virtual ~AttributeComponent();

//Accessors:

	const bool isDead() const;

//Functions:

	std::string debugPrint() const;

	void loseHp(const int hp);
	void gainHp(const int hp);

	void loseExp(const int exp);
	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

