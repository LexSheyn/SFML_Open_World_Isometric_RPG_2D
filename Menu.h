#pragma once

class Menu
{
private:

	//

protected:

	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;

//	std::map<std::string, gui::Button*> buttons;
	std::map<const gui::ButtonName, gui::Button*> buttons;

// protected: Functions:

	void initTexture(sf::Texture& texture, const std::string file_path);

public:

// Constructors and Destructors:

	Menu(sf::VideoMode& video_mode, sf::Font& font);
	virtual ~Menu();

// Accessors:

//	std::map<std::string, gui::Button*>& getButtons();
	std::map<const gui::ButtonName, gui::Button*>& getButtons();

// Functions:

//	const bool isButtonPressed(const std::string key);
//	void addButton
//	(
//		const std::string key,
//		const float y,
//		const float width,
//		const float height,
//		const unsigned char_size,
//		const std::string text
//	);

	const bool isButtonPressed(const gui::ButtonName name);
	void addButton
	(
		const gui::ButtonName name,
		const float y,
		const float width,
		const float height,
		const unsigned char_size,
		const std::string text
	);

	virtual void update(const sf::Vector2i& mouse_position, const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};
