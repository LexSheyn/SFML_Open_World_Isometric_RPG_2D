#include "stdafx.h"
#include "TextTagSystem.h"

// private: Functions:

void TextTagSystem::initVariables()
{
	
}

void TextTagSystem::initFont(const std::string file_path)
{
	if (!this->font.loadFromFile(file_path))
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::initFont::Failed to load: " << file_path << std::endl;
	}
}

void TextTagSystem::initTagTemplates()
{
	sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	this->tagTemplates[TagTypes::Default] = new TextTag(100.f, 100.f, 0.f, -1.f, this->font, "TEST", sf::Color::White, gui::calculateCharSize(3.f, vm), 100.f, 50.f);
	this->tagTemplates[TagTypes::Negative] = new TextTag(100.f, 100.f, 0.f, -1.f, this->font, "TEST", sf::Color(255, 50, 0), gui::calculateCharSize(3.f, vm), 100.f, 50.f);
	this->tagTemplates[TagTypes::Positive] = new TextTag(100.f, 100.f, 0.f, -1.f, this->font, "TEST", sf::Color(50, 255, 0), gui::calculateCharSize(3.f, vm), 100.f, 50.f);
	this->tagTemplates[TagTypes::Experience] = new TextTag(100.f, 100.f, 0.f, -1.f, this->font, "TEST", sf::Color::Yellow, gui::calculateCharSize(4.f, vm), 150.f, 50.f);
}


// Constructors and Distructor:

TextTagSystem::TextTagSystem(StateData* state_data, const std::string font_file_path)
{
	this->initVariables();

	this->stateData = state_data;

	this->initFont(font_file_path);
	
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
	// Deleting text tags
	for (auto* tag : this->tags)
	{
		delete tag;
	}
	this->tags.clear();

	// Deleting tag templates
	for (auto& tag_template : this->tagTemplates)
	{
		delete tag_template.second;
	}
	this->tagTemplates.clear();
}


// Functions:

void TextTagSystem::addTextTag
(
	const TagTypes tag_type, const float x, const float y,
	const std::string str, const std::string prefix, const std::string postfix
)
{
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], x, y, prefix + " " + str + " " + postfix));
}

void TextTagSystem::addTextTag
(
	const TagTypes tag_type, const float x, const float y, const int int_value,
	const std::string prefix, const std::string postfix
)
{
//	std::stringstream ss;
//
//	ss << value;
//
//	this->tags.push_back(new TextTag(this->tagTemplates[TagTypes::Default], x, y, ss.str()));

	// More than 2 times faster than std::stringstream
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], x, y, prefix + " " + std::to_string(int_value) + " " + postfix));
}

void TextTagSystem::addTextTag
(
	const TagTypes tag_type, const float x, const float y, const float float_value,
	const std::string prefix, const std::string postfix
)
{
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], x, y, prefix + " " + std::to_string(float_value) + " " + postfix));
}

void TextTagSystem::update(const float& dt)
{
	for (size_t i = 0; i < this->tags.size(); i++)
	{
		this->tags[i]->update(dt);

		if (this->tags[i]->isExpired())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}
