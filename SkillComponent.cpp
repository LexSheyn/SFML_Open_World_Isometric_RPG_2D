#include "stdafx.h"
#include "SkillComponent.h"

//Constructors and Destructor:

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(SKILLS::HEALTH));
	this->skills.push_back(Skill(SKILLS::ATTACK));
	this->skills.push_back(Skill(SKILLS::ACCURACY));
	this->skills.push_back(Skill(SKILLS::ENDURANCE));
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkillLevel(const int skill) const
{
	if (skills.empty() || skill < 0 || static_cast<size_t>(skill) >= this->skills.size())
	{
		//	std::cout << "ERROR::SkillComponent::Skill does not exist: " << key << std::endl;
		throw "ERROR::SkillComponent::getSkillLevel::Skill does not exist: " + skill;
	}
	else
	{
		return this->skills[skill].getLevel();
	}

	return -1;
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (skills.empty() || skill < 0 || static_cast<size_t>(skill) >= this->skills.size())
	{
		//	std::cout << "ERROR::SkillComponent::Skill does not exist: " << key << std::endl;
		throw "ERROR::SkillComponent::gainExp::Skill does not exist: " + skill;
	}
	else
	{
		this->skills[skill].gainExp(exp);
	}
}
