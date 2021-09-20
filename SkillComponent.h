#pragma once

enum SKILLS
{
	HEALTH = 0,
	ATTACK,
	ACCURACY,
	ENDURANCE
};

class SkillComponent
{
private:

	class Skill
	{
	private:

	//Variables:

		int type;
		int level;
		int levelMax;
		int exp;
		int expNext;

	public:

	//Constructors and Destructor:

		Skill(const int type)
		{
			this->type = type;
			this->level = 1;
			this->levelMax = 99;
			this->exp = 0;
			this->expNext = 100;
		}

		~Skill() {}

	//Accessors:

		inline const int& getType() const { return this->type; }
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

	//Modifiers:

		inline void setLevel(const int level) { this->level = level; }
		inline void setLevelMax(const int level_max) { this->levelMax = level_max; }

	//Functions:

		void gainExp(const int exp)
		{
			this->exp += exp;
			this->updateLevel();
		}

		void loseExp(const int exp)
		{
			this->exp -= exp;
		}

		//Updates level of the skill.
		//If "up" is set to TRUE - increases level when exp reaches expNext value.
		//If "up" is set to FALSE - decreases level when exp reaches 0.
		void updateLevel(const bool up = true)
		{
			if (up)
			{
				if (this->level < this->levelMax)
				{
					if (this->exp >= this->expNext)
					{
						this->level++;
						this->exp -= this->expNext;
						this->expNext = static_cast<int>(std::pow(static_cast<float>(this->level), 2.f)) + this->level * 10 + this->level * 2;
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					if (this->exp < 0)
					{
						this->level--;
						this->expNext = static_cast<int>(std::pow(static_cast<float>(this->level), 2.f)) + this->level * 10 + this->level * 2;
						this->exp += this->expNext;
					}
				}
			}
		}

		void update()
		{

		}
	};

	std::vector<Skill> skills;

public:

//Constructors and Distructors:

	SkillComponent();
	virtual ~SkillComponent();

//Accessors:

	const int getSkillLevel(const int skill) const;

//Functions:

	const void gainExp(const int skill, const int exp);
};

