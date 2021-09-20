#include "stdafx.h"
#include "Gui.h"

//Converts a percentage value to pixels relative to current resolution in the X axis.
//@param	float percent			The percentage value.
//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
//@return	float				The calculated pixel value.
const float gui::percentIntoX(const float percent, const sf::VideoMode& video_mode)
{
	return std::floor(static_cast<float>(video_mode.width) * (percent / 100.f));
}

//Converts a percentage value to pixels relative to current resolution in the Y axis.
//@param	float percent			The percentage value.
//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
//@return	float				The calculated pixel value.
const float gui::percentIntoY(const float percent, const sf::VideoMode& video_mode)
{
	return std::floor(static_cast<float>(video_mode.height) * (percent / 100.f));
}

//Calculates the character size for text using the current resolution and a constant.
//@param	float percent			The percentage value.
//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
//@return	unsigned			The calculated character size value.
const unsigned gui::calculateCharSize(const float percent, const sf::VideoMode& video_mode)
{
	if (video_mode.width > video_mode.height)
	{
		return static_cast<unsigned>(std::floor(static_cast<float>(video_mode.height) * (percent / 100.f)));
	}

	return static_cast<unsigned>(std::floor(static_cast<float>(video_mode.width) * (percent / 100.f)));

	//	return (this->stateData->gfxSettings->resolution.width + this->stateData->gfxSettings->resolution.height) / 100;
}








//Button class ====================================================================================================

//private: Functions:
void gui::Button::initVariables()
{
	this->fontSize = 20;

	this->colorNumber = 0;
//	this->colorMaxStages = 6;

	this->stepOutline = 0.034f;
	this->stepButton = 0.1f;
	this->stepText = 0.034f;

	this->coefficientOutline = 0.8f;
	this->coefficientButton = 0.4f;
	this->coefficientText = 0.8f;

	this->buttonTimer = 0.f;
	this->buttonTimerMax = 4.f;
}

//Constructors and Destructor:

gui::Button::Button
(
	const float x, const float y, const float width, const float height,
	sf::Font* font, const std::string& str, const uint32_t font_size,
	sf::Color button_idle_color, sf::Color button_hover_color, sf::Color button_active_color,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color outline_idle_color,
	sf::Color outline_hover_color,
	sf::Color outline_active_color,
	const uint32_t id
)
{
	this->initVariables();

	this->buttonState = gui::ButtonStates::Idle;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(-1.f);
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(str);	
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(font_size);
	this->text.setPosition
	(
		(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f)) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y// + (this->shape.getGlobalBounds().height / 20.f))// - (this->text.getGlobalBounds().height / 2.f)
	);

	// Outline colors
	this->outlineIdleColor =   outline_idle_color;
	this->outlineHoverColor =  outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	// Button colors
	this->buttonIdleColor =   button_idle_color;
	this->buttonHoverColor =  button_hover_color;
	this->buttonActiveColor = button_active_color;

	// Text colors
	this->textIdleColor =   text_idle_color;
	this->textHoverColor =  text_hover_color;
	this->textActiveColor = text_active_color;

	// Outline idle to hover color
	this->idleToHoverColorOutline[0] = this->outlineIdleColor;
	this->coefficientOutline += this->stepOutline;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorOutline[i].r = static_cast<unsigned>(static_cast<float>(outline_hover_color.r) * this->coefficientOutline);
		this->idleToHoverColorOutline[i].g = static_cast<unsigned>(static_cast<float>(outline_hover_color.g) * this->coefficientOutline);
		this->idleToHoverColorOutline[i].b = static_cast<unsigned>(static_cast<float>(outline_hover_color.b) * this->coefficientOutline);
		this->coefficientOutline += this->stepOutline;
	}

	//Button idle to hover color
	this->idleToHoverColorButton[0] = this->buttonIdleColor;
	this->coefficientButton += this->stepButton;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorButton[i].r = static_cast<unsigned>(static_cast<float>(button_hover_color.r) * this->coefficientButton);
		this->idleToHoverColorButton[i].g = static_cast<unsigned>(static_cast<float>(button_hover_color.g) * this->coefficientButton);
		this->idleToHoverColorButton[i].b = static_cast<unsigned>(static_cast<float>(button_hover_color.b) * this->coefficientButton);
		this->coefficientButton += this->stepButton;
	}

	//Text idle to hover color
	this->idleToHoverColorText[0] = this->textIdleColor;
	this->coefficientText += this->stepText;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorText[i].r = static_cast<unsigned>(static_cast<float>(text_hover_color.r) * this->coefficientText);
		this->idleToHoverColorText[i].g = static_cast<unsigned>(static_cast<float>(text_hover_color.g) * this->coefficientText);
		this->idleToHoverColorText[i].b = static_cast<unsigned>(static_cast<float>(text_hover_color.b) * this->coefficientText);
		this->coefficientText += this->stepText;
	}

	// Outline
	this->shape.setOutlineColor(this->outlineIdleColor);

	// Button
	this->shape.setFillColor(this->buttonIdleColor);

	// Text
	this->text.setFillColor(this->textIdleColor);
}

gui::Button::Button
(
	const float x, const float y, const float width, const float height,
	sf::Font* font, const std::string& text, const uint32_t font_size,
	sf::Color auto_outline_hover_color,
	sf::Color auto_button_hover_color,
	sf::Color auto_text_hover_color,
	const uint32_t id
)
{
	this->initVariables();

	this->buttonState = gui::ButtonStates::Idle;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(-1.f);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(font_size);
	this->text.setPosition
	(
		(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f)) - (this->text.getGlobalBounds().width / 2.f),
		(this->shape.getPosition().y + 1000.f)// + (this->shape.getGlobalBounds().height / 20.f))// - (this->text.getGlobalBounds().height / 2.f)
	);

//Colors check:

	//Button
	if (auto_button_hover_color.r < 60 && auto_button_hover_color.g < 60 && auto_button_hover_color.b < 60)
	{
		auto_button_hover_color.r += 130;
		auto_button_hover_color.g += 130;
		auto_button_hover_color.b += 130;
	}

	//Text
//	if (auto_text_hover_color.r < 60 && auto_text_hover_color.g < 60 && auto_text_hover_color.b < 60)
//	{
//		auto_text_hover_color.r += 160;
//		auto_text_hover_color.g += 160;
//		auto_text_hover_color.b += 160;
//	}

// Outline colors:

	//Idle color
	this->outlineIdleColor.r = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.r) * 0.7f);
	this->outlineIdleColor.g = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.g) * 0.7f);
	this->outlineIdleColor.b = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.b) * 0.7f);
	this->outlineIdleColor.a = 200;

	//Hover color
	this->outlineHoverColor = auto_outline_hover_color;
	this->outlineHoverColor.a = 255;

	//Active color
	this->outlineActiveColor.r = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.r) * 0.4f);
	this->outlineActiveColor.g = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.g) * 0.4f);
	this->outlineActiveColor.b = static_cast<uint32_t>(static_cast<float>(auto_outline_hover_color.b) * 0.4f);
	this->outlineActiveColor.a = 200;

// Button colors:

	//Idle color
	this->buttonIdleColor.r = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.r) * 0.4f);
	this->buttonIdleColor.g = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.g) * 0.4f);
	this->buttonIdleColor.b = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.b) * 0.4f);
	this->buttonIdleColor.a = 200;

	//Hover color
	this->buttonHoverColor = auto_button_hover_color;
	this->buttonHoverColor.a = 255;

	//Active color
	this->buttonActiveColor.r = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.r) * 0.1f);
	this->buttonActiveColor.g = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.g) * 0.1f);
	this->buttonActiveColor.b = static_cast<uint32_t>(static_cast<float>(auto_button_hover_color.b) * 0.1f);
	this->buttonActiveColor.a = 200;

//Text colors:

	//Idle color
	this->textIdleColor.r = static_cast<uint32_t>(static_cast<float>(auto_text_hover_color.r) * 0.7f);
	this->textIdleColor.g = static_cast<uint32_t>(static_cast<float>(auto_text_hover_color.g) * 0.7f);
	this->textIdleColor.b = static_cast<uint32_t>(static_cast<float>(auto_text_hover_color.b) * 0.7f);
	this->textIdleColor.a = 255;

	//Hover color
	this->textHoverColor = auto_text_hover_color;
	this->textHoverColor.a = 255;

	//Active color
	this->textActiveColor.r = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.r) * 0.4f);
	this->textActiveColor.g = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.g) * 0.4f);
	this->textActiveColor.b = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.b) * 0.4f);
	this->textActiveColor.a = 255;

	// Outline idle to hover color
	this->idleToHoverColorOutline[0] = this->outlineIdleColor;
	this->coefficientOutline += this->stepOutline;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorOutline[i].r = static_cast<unsigned>(static_cast<float>(auto_outline_hover_color.r) * this->coefficientOutline);
		this->idleToHoverColorOutline[i].g = static_cast<unsigned>(static_cast<float>(auto_outline_hover_color.g) * this->coefficientOutline);
		this->idleToHoverColorOutline[i].b = static_cast<unsigned>(static_cast<float>(auto_outline_hover_color.b) * this->coefficientOutline);
		this->coefficientOutline += this->stepOutline;
	}

	// Button idle to hover color
	this->idleToHoverColorButton[0] = this->buttonIdleColor;
	this->coefficientButton += this->stepText;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorButton[i].r = static_cast<unsigned>(static_cast<float>(auto_button_hover_color.r) * this->coefficientButton);
		this->idleToHoverColorButton[i].g = static_cast<unsigned>(static_cast<float>(auto_button_hover_color.g) * this->coefficientButton);
		this->idleToHoverColorButton[i].b = static_cast<unsigned>(static_cast<float>(auto_button_hover_color.b) * this->coefficientButton);
		this->coefficientButton += this->stepButton;
	}

	// Text idle to hover color
	this->idleToHoverColorText[0] = this->textIdleColor;
	this->coefficientText += this->stepText;
	for (unsigned short i = 1; i < this->colorMaxStages; i++)
	{
		this->idleToHoverColorText[i].r = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.r) * this->coefficientText);
		this->idleToHoverColorText[i].g = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.g) * this->coefficientText);
		this->idleToHoverColorText[i].b = static_cast<unsigned>(static_cast<float>(auto_text_hover_color.b) * this->coefficientText);
		this->coefficientText += this->stepText;
	}

	// Outline
	this->shape.setOutlineColor(this->outlineIdleColor);

	// Button
	this->shape.setFillColor(this->buttonIdleColor);
	
	// Text
	this->text.setFillColor(this->textIdleColor);
}


gui::Button::~Button()
{

}

// Accessors:

const bool gui::Button::isPressed() const
{
	if (this->buttonState == gui::ButtonStates::Active)
	{
		return true;
	}
	
	return false;
}

const std::string gui::Button::getString() const
{
	return this->text.getString();
}

const uint32_t& gui::Button::getId() const
{
	return this->id;
}

// Modifiers:

void gui::Button::setString(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const uint32_t id)
{
	this->id = id;
}

// Functions:

// Updates the booleans for hover and pressed.
void gui::Button::update(const sf::Vector2i& mouse_position, bool update_buttons, bool update_text)
{
	// Hover
	if (this->shape.getGlobalBounds().contains(sf::Vector2f(mouse_position)))
	{
		this->buttonState = gui::ButtonStates::Hover;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = gui::ButtonStates::Active;
		}
	}
	else
	{
		// Idle
		this->buttonState = gui::ButtonStates::Idle;
	}

	switch (this->buttonState)
	{
	case gui::ButtonStates::Idle:

		if (update_buttons)
		{
			this->shape.setOutlineColor(this->currentColorOutline);
			this->shape.setFillColor(this->currentColorButton);
		}
		else
		{
			this->shape.setOutlineColor(this->outlineIdleColor);
			this->shape.setFillColor(this->buttonIdleColor);
		}

		if (update_text)
		{
			this->text.setFillColor(this->currentColorText);
		}
		else
		{
			this->text.setFillColor(this->textIdleColor);
		}

		break;

	case gui::ButtonStates::Hover:

		if (update_buttons)
		{
			this->shape.setOutlineColor(this->currentColorOutline);
			this->shape.setFillColor(this->currentColorButton);
		}
		else
		{
			this->shape.setOutlineColor(this->outlineHoverColor);
			this->shape.setFillColor(this->buttonHoverColor);
		}

		if (update_text)
		{
			this->text.setFillColor(this->currentColorText);
		}
		else
		{
			this->text.setFillColor(this->textHoverColor);
		}		

		break;

	case gui::ButtonStates::Active:

		this->shape.setOutlineColor(this->outlineActiveColor);
		this->shape.setFillColor(this->buttonActiveColor);
		this->text.setFillColor(this->textActiveColor);

		break;

	default:

		this->shape.setOutlineColor(sf::Color::Green);
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);

		break;
	}
}

void gui::Button::updateButtonColor(const float& dt)
{
	if (this->buttonState == gui::ButtonStates::Hover)
	{
		this->buttonTimer += 100.f * dt;
		if (this->buttonTimer >= this->buttonTimerMax)
		{
			this->buttonTimer = 0.f;
			this->currentColorOutline = this->idleToHoverColorOutline[static_cast<uint32_t>(this->colorNumber)];
			this->currentColorButton = this->idleToHoverColorButton[static_cast<uint32_t>(this->colorNumber)];
			this->currentColorText = this->idleToHoverColorText[static_cast<uint32_t>(this->colorNumber)];

			if (static_cast<uint32_t>(this->colorNumber) < (this->colorMaxStages - 1))
			{
				++this->colorNumber;
			}
		}
	}
	else if (this->buttonState == gui::ButtonStates::Idle)
	{
		this->buttonTimer += 100.f * dt;
		if (this->buttonTimer >= this->buttonTimerMax)
		{
			this->buttonTimer = 0.f;
			this->currentColorOutline = this->idleToHoverColorOutline[static_cast<uint32_t>(this->colorNumber)];
			this->currentColorButton = this->idleToHoverColorButton[static_cast<uint32_t>(this->colorNumber)];
			this->currentColorText = this->idleToHoverColorText[static_cast<uint32_t>(this->colorNumber)];

			if (this->colorNumber > 0)
			{
				--this->colorNumber;
			}
		}
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}








//DropDownList class ====================================================================================================

//Constructors and Destructor:

gui::DropDownList::DropDownList
(
	float x, float y, float width, float height,
	sf::Font& font, unsigned int font_size, std::string list[],
	unsigned number_of_elements, unsigned default_index
)
	: font(font), showList(false), keytimeMax(30.f), keytime(0.f)
{
	//unsigned numberOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button
	(
		x, y, width, height,
		&this->font, list[default_index], font_size,
		sf::Color(80, 80, 0, 200), sf::Color(255, 255, 0, 230), sf::Color(0, 0, 0, 200),
		sf::Color::Yellow, sf::Color::Black, sf::Color::White,
		sf::Color(102, 102, 0, 255), sf::Color(255, 255, 0, 255), sf::Color(0, 0, 0, 255)
	);

	for (unsigned i = 0; i < number_of_elements; i++)
	{
		this->list.push_back
		(
			new gui::Button
			(
				x, y + ((i + 1) * height), width, height,
				&this->font, list[i], font_size,
				sf::Color(80, 80, 0, 200), sf::Color(255, 255, 0, 230), sf::Color(0, 0, 0, 200),
				sf::Color::Yellow, sf::Color::Black, sf::Color::White,
				sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
				i
			)
		);
	}
}

gui::DropDownList::DropDownList
(
	float x, float y, float width, float height,
	sf::VideoMode video_mode,
	sf::Font& font, unsigned int font_size, std::string list[],
	unsigned number_of_elements, unsigned default_index
)
	: font(font), showList(false), keytimeMax(30.f), keytime(0.f)
{
	//unsigned numberOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button
	(
		x, y, width, height,
		&this->font, list[default_index], font_size,
		sf::Color(80, 80, 0, 200), sf::Color(255, 255, 0, 230), sf::Color(0, 0, 0, 200),
		sf::Color::Yellow, sf::Color::Black, sf::Color::White,
		sf::Color(102, 102, 0, 255), sf::Color(255, 255, 0, 255), sf::Color(0, 0, 0, 255)
	);

	this->strWidth = std::to_string(video_mode.width);
	this->strHeight = std::to_string(video_mode.height);

	this->activeElement->setString(this->strWidth + " x " + this->strHeight);

	for (unsigned i = 0; i < number_of_elements; i++)
	{
		this->list.push_back
		(
			new gui::Button
			(
				x, y + ((i + 1) * height), width, height,
				&this->font, list[i] , font_size,
				sf::Color(80, 80, 0, 200), sf::Color(255, 255, 0, 230), sf::Color(0, 0, 0, 200),
				sf::Color::Yellow, sf::Color::Black, sf::Color::White,
				sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
				i
			)
		);
	}	
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;

	for (auto*& i : this->list)
	{
		delete i;
	}
}

//Accessors:

const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0;
		return true;
	}

	return false;
}

const uint32_t& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions:

void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2i& mouse_position, const float& dt)
{
	this->updateKeytime(dt);

	//Dropdown list's active element
	this->activeElement->update(mouse_position, true);
	this->activeElement->updateButtonColor(dt);

	//Showing and hiding the dropdown list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
		{
			this->showList = false;
		}
		else
		{
			this->showList = true;
		}
	}

	//When the dropdown list is showing up
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mouse_position, true);
			i->updateButtonColor(dt);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;

				// Pointless because recreating the window recreates all this too
				this->activeElement->setString(i->getString());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}








//TextureSelector class ====================================================================================================

//Constructors and Destructor:

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
	: keytimeMax(30.f), keytime(0.f)
{
	this->gridSize = grid_size;
	this->active = false;
	this->hidden = false;
	float offset = grid_size;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);
	
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect
		(
			0, 
			0, 
			static_cast<int>(this->bounds.getGlobalBounds().width), 
			static_cast<int>(this->sheet.getGlobalBounds().height))
		);
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect
		(
			0, 
			0, 
			static_cast<int>(this->sheet.getGlobalBounds().width),
			static_cast<int>(this->bounds.getGlobalBounds().height))
		);
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(grid_size, grid_size));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(grid_size);
	this->textureRect.height = static_cast<int>(grid_size);

	this->hide_button = new gui::Button
	(
		x, y, 40.f, 40.f,
		&font, text, 20,
		sf::Color(74, 74, 74, 200), sf::Color(115, 115, 0, 200), sf::Color(25, 25, 0, 150),
		sf::Color(204, 204, 204), sf::Color(255, 255, 0), sf::Color(255, 155, 0)
	);
}

gui::TextureSelector::~TextureSelector()
{
	//Deleting buttons
	delete this->hide_button;
}

//Accessors:

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0;
		return true;
	}

	return false;
}

const bool& gui::TextureSelector::isActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

//Functions:

void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}

void gui::TextureSelector::update(const sf::Vector2i& mouse_position_window, const float& dt)
{
	this->updateKeytime(dt);

	this->hide_button->update(mouse_position_window);

	if (this->hide_button->isPressed() && this->getKeytime())
	{
		if (this->hidden)
		{
			this->hidden = false;
		}
		else
		{
			this->hidden = true;
		}
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position_window)))
		{
			this->active = true;

			this->mousePositionGrid.x = (static_cast<unsigned>(mouse_position_window.x) - static_cast<unsigned>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePositionGrid.y = (static_cast<unsigned>(mouse_position_window.y) - static_cast<unsigned>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
			this->selector.setPosition
			(
				this->bounds.getPosition().x + (this->mousePositionGrid.x * this->gridSize),
				this->bounds.getPosition().y + (this->mousePositionGrid.y * this->gridSize)
			);
		}
		else
		{
			this->active = false;
		}

		//Updating texture rectangle
		this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
		this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
		{
			target.draw(this->selector);
		}
	}

	this->hide_button->render(target);
}








//ProgressBar class ====================================================================================================

//Constructors and Destructor:

gui::ProgressBar::ProgressBar(float x, float y, float width, float height, sf::Font* font, unsigned int char_size)
{
	this->widthMax = width;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition(x, y);

	this->inner.setSize(this->back.getSize());
	this->inner.setFillColor(sf::Color(250, 20, 20, 200));
	this->inner.setPosition(this->back.getPosition());

	this->fontPointer = font;
	
	if (font)
	{
		this->text.setFont(*font);
		this->text.setCharacterSize(char_size);
		this->text.setString("0");
		this->text.setPosition
		(
			this->back.getPosition().x + (this->back.getGlobalBounds().width / 10.f),
			this->back.getPosition().y + (this->back.getGlobalBounds().height / 10.f)
		);
	}
}

gui::ProgressBar::~ProgressBar()
{

}

//Accessors:

	//


//Modifiers:

void gui::ProgressBar::setBackColor(const sf::Color& color)
{
	this->back.setFillColor(color);
}

void gui::ProgressBar::setBackTexture(const std::string& file_path)
{
	this->backTexture.loadFromFile(file_path);
	this->back.setTexture(&this->backTexture);
}

void gui::ProgressBar::setInnerColor(const sf::Color& color)
{
	this->inner.setFillColor(color);
}

void gui::ProgressBar::setInnerTexture(const std::string& file_path)
{
	this->innerTexture.loadFromFile(file_path);
	this->inner.setTexture(&this->innerTexture);
}

void gui::ProgressBar::setPosition(const float x, const float y)
{
	this->back.setPosition(x, y);
	this->inner.setPosition(x, y);
}

void gui::ProgressBar::setPosition(const sf::Vector2f& position)
{
	this->back.setPosition(position);
	this->inner.setPosition(position);
}

void gui::ProgressBar::setTextString(const std::string& str)
{
	this->text.setString(str);
}

void gui::ProgressBar::setTextPosition(const float x, const float y)
{
	this->text.setPosition(x, y);
}

void gui::ProgressBar::setTextPosition(const sf::Vector2f& position)
{
	this->text.setPosition(position);
}


//Functions:

void gui::ProgressBar::update(const int current_value, const int max_value, const float& dt, const bool update_color)
{
	float percent = static_cast<float>(current_value / static_cast<float>(max_value));	

	this->inner.setSize
	(
		sf::Vector2f(
			static_cast<float>(std::floor(this->widthMax * percent)),
			this->inner.getSize().y
		)
	);

	if (this->fontPointer)
	{
		this->barString = std::to_string(current_value) + " / " + std::to_string(max_value);
		this->text.setString(this->barString);
	}

	if (update_color)
	{
		float color = 254.f;
		this->inner.setFillColor(sf::Color(static_cast<unsigned char>(color - pow(color, percent)), static_cast<unsigned char>(color * (percent)), 20, 200));
	}
}

void gui::ProgressBar::render(sf::RenderTarget& target)
{
	target.draw(this->back);

	target.draw(this->inner);

	if (this->fontPointer)
	{
		target.draw(this->text);
	}
}