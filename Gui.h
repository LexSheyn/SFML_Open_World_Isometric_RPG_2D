#pragma once

namespace gui
{
	enum class ButtonName
	{
		Start = 0,
		Settings,
		Editor,
		Exit,
		Resume,
		Save,
		Load,
		Quit,
		Apply,
		Back
	};

	enum class ButtonStates
	{
		Idle = 0,
		Hover,
		Active
	};

	//Converts a percentage value to pixels relative to current resolution in the X axis.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	float				The calculated pixel value.
	const float percentIntoX(const float percent, const sf::VideoMode& video_mode);

	//Converts a percentage value to pixels relative to current resolution in the Y axis.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	float				The calculated pixel value.
	const float percentIntoY(const float percent, const sf::VideoMode& video_mode);

	//Calculates the character size for text using the current resolution and a constant.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	unsigned			The calculated character size value.
	const unsigned calculateCharSize(const float percent, const sf::VideoMode& video_mode);

	class Button
	{
	private:

	//Variables:

		ButtonStates buttonState;
		uint32_t id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		uint32_t fontSize;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		sf::Color buttonIdleColor;
		sf::Color buttonHoverColor;
		sf::Color buttonActiveColor;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color currentColorOutline;
		sf::Color currentColorButton;
		sf::Color currentColorText;

		int32_t colorNumber;
		const static uint32_t colorMaxStages = 6;

		sf::Color idleToHoverColorOutline[colorMaxStages];
		sf::Color idleToHoverColorButton[colorMaxStages];
		sf::Color idleToHoverColorText[colorMaxStages];

		float stepOutline;
		float stepButton;
		float stepText;

		float coefficientOutline;
		float coefficientButton;
		float coefficientText;

		float buttonTimer;
		float buttonTimerMax;

	//private: Functions:

		void initVariables();

	public:

	//Constructors and Destructor:

		Button
		(
			const float x, const float y, const float width, const float height,
			sf::Font* font, const std::string& str, const uint32_t font_size,
			sf::Color button_idle_color, sf::Color button_hover_color, sf::Color button_active_color,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, 
			sf::Color outline_hover_color = sf::Color::Transparent, 
			sf::Color outline_active_color = sf::Color::Transparent,
			const uint32_t id = 0
		);
		Button
		(
			const float x, const float y, const float width, const float height,
			sf::Font* font, const std::string& text, const uint32_t font_size,
			sf::Color auto_outline_hover_color = sf::Color::Transparent,
			sf::Color auto_button_hover_color = sf::Color::Cyan,
			sf::Color auto_text_hover_color = sf::Color::Black,
			const uint32_t id = 0
		);
		virtual ~Button();

	//Accessors:

		const bool isPressed() const;
		const std::string getString() const;
		const uint32_t& getId() const;

	//Modifiers:

		void setString(const std::string str);
		void setId(const uint32_t id);

	//Fucntions:

		void update(const sf::Vector2i& mouse_position, bool update_buttons = false, bool update_text = false);
		void updateButtonColor(const float& dt);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:

	//Variables:

		float keytime;
		const float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		std::string strWidth;
		std::string strHeight;

	public:

	//Constructors and Destructor:

		DropDownList
		(
			float x, float y, float width, float height,
			sf::Font& font, unsigned int font_size, std::string list[],
			unsigned number_of_elements, unsigned default_index = 0
		);
		DropDownList
		(
			float x, float y, float width, float height,
			sf::VideoMode video_mode,
			sf::Font& font, unsigned int font_size, std::string list[], 
			unsigned number_of_elements, unsigned default_index = 0
		);
		virtual ~DropDownList();

	//Accessors:

		const bool getKeytime();
		const uint32_t& getActiveElementId() const;

	//Fucntions:
				
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mouse_position, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:

		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_button;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePositionGrid;
		sf::IntRect textureRect;

	public:

	//Constructors and Destructor:

		TextureSelector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		virtual ~TextureSelector();

	//Accessors:

		const bool getKeytime();
		const bool& isActive() const;
		const sf::IntRect& getTextureRect() const;

	//Functions:

		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mouse_position_window, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar
	{
	private:

	//Variables:

		std::string barString;
		sf::Text text;
		sf::Font* fontPointer;
		float widthMax;
	//	int valueMax;
		sf::RectangleShape back;
		sf::RectangleShape inner;
		sf::Texture backTexture;
		sf::Texture innerTexture;

	public:

	//Constructors and Destructor:

		ProgressBar(float x, float y, float width, float height, sf::Font* font = nullptr, unsigned int char_size = 20u);
		virtual ~ProgressBar();

	//Accessors:

		//

	//Modifiers:

		void setBackColor(const sf::Color& color);
		void setBackTexture(const std::string& file_path);

		void setInnerColor(const sf::Color& color);
		void setInnerTexture(const std::string& file_path);

		void setPosition(const float x, const float y);
		void setPosition(const sf::Vector2f& position);

		void setTextString(const std::string& str);

		void setTextPosition(const float x, const float y);
		void setTextPosition(const sf::Vector2f& position);

	//Functions:

		void update(const int current_value, const int max_value, const float& dt, const bool update_color = false);
		
		void render(sf::RenderTarget& target);
	};
}

