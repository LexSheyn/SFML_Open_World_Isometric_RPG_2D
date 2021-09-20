#pragma once

#include "State.h"

enum class TagTypes
{
	Default = 0,
	Negative,
	Positive,
	Experience,
	Environmental
};

class TextTagSystem
{
private:

// Nested class:

	class TextTag
	{
	private:

	// Variables:

		sf::Text text;
		float dirX;
		float dirY;
		float lifetime;
		float speed;

	public:

	// Constructors and Distructor:

		TextTag
		(
			float x, float y,
			float dir_x, float dir_y,
			sf::Font& font, std::string str,
			sf::Color color,
			unsigned int char_size,
			float lifetime, float speed
		)
		{
			this->text.setFont(font);
			this->text.setPosition(x, y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(str);
			
			this->dirX = dir_x;
			this->dirY = dir_y;

			this->lifetime = lifetime;
			this->speed = speed;
		}

		TextTag
		(
			TextTag* tag,
			float x, float y,
			std::string str
		)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(x, y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;

			this->lifetime = tag->lifetime;
			this->speed = tag->speed;
		}

		~TextTag()
		{

		}

	//Accessors:

		inline const bool isExpired() const { return this->lifetime <= 0.f; }

	// Functions:

		void update(const float& dt)
		{
			if (this->lifetime > 0.f)
			{
				// Updating lifetime
				this->lifetime -= 100.f * dt;

				// Moving tag
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
			}
		}

		void render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

// Variables:

	sf::Font font;
//	std::map<const int, TextTag*> textTagTemplates;
	std::map<const TagTypes, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	StateData* stateData;

// private: Functions:

	void initVariables();
	void initFont(const std::string file_path);
	void initTagTemplates();

public:

// Constructors and Distructor:

	TextTagSystem(StateData* state_data, const std::string font_file_path);
	virtual ~TextTagSystem();
	
// Functions:

//	void addTextTag(const int tag_type);
	void addTextTag
	(
		const TagTypes tag_type, const float x, const float y, 
		const std::string str, const std::string prefix = "", const std::string postfix = ""
	);
	void addTextTag
	(
		const TagTypes tag_type, const float x, const float y, const int int_value, 
		const std::string prefix = "", const std::string postfix = ""
	);
	void addTextTag
	(
		const TagTypes tag_type, const float x, const float y, const float float_value, 
		const std::string prefix = "", const std::string postfix = ""
	);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

