#include "stdafx.h"
#include "PlayerGui.h"

//private: Functions:

//Should use '../' before the file path to be able to play the game without Visual Studio.
void PlayerGui::initFont(sf::Font& font_name, const std::string file_path)
{
	if (!font_name.loadFromFile(file_path))
	{
		std::cout << "ERROR::PlayerGui::initFont::Failed to load " << file_path << std::endl;
	}
}

void PlayerGui::initHpBar()
{
	this->hpBar = new gui::ProgressBar
	(
		gui::percentIntoX(2.f, this->vm),
		gui::percentIntoY(3.f, this->vm),
		gui::percentIntoX(25.5f, this->vm),
		gui::percentIntoY(4.5f, this->vm),
		&this->font, 
		gui::calculateCharSize(2.7f, this->vm)
	);

	this->hpBar->setInnerTexture("Resources/Images/GUI/Player/health_bar.png");
}

void PlayerGui::initLevelBar()
{
	float width = gui::percentIntoX(2.5f, this->vm);
	float height = gui::percentIntoY(4.5f, this->vm);
	float x = gui::percentIntoX(2.f, this->vm);
	float y = gui::percentIntoY(9.f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

//	this->levelBarTexture.loadFromFile("Resources/Images/GUI/Player/level_bar.png");
//	this->levelBarBack.setTexture(&this->levelBarTexture);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calculateCharSize(2.7f, this->vm));
	this->levelBarText.setPosition
	(
		this->levelBarBack.getPosition().x + (this->levelBarBack.getGlobalBounds().width / 2.7f), 
		this->levelBarBack.getPosition().y + (this->levelBarBack.getGlobalBounds().height / 6.f)
	);
}

void PlayerGui::initExpBar()
{
	float width = gui::percentIntoX(17.f, this->vm);
	float height = gui::percentIntoY(3.f, this->vm);
	float x = gui::percentIntoX(5.1f, this->vm);
	float y = gui::percentIntoY(9.f, this->vm);

	this->expBar = new gui::ProgressBar
	(
		gui::percentIntoX(5.1f, this->vm),
		gui::percentIntoY(9.f, this->vm),
		gui::percentIntoX(17.f, this->vm),
		gui::percentIntoY(3.f, this->vm),
		&this->font,
		gui::calculateCharSize(2.f, this->vm)
	);

	this->expBar->setInnerTexture("Resources/Images/GUI/Player/experience_bar.png");
	this->expBar->setInnerColor(sf::Color(120, 20, 250, 200));
}

void PlayerGui::initPlayerTabPanel()
{
	this->playerTabs = new PlayerTabPanel(this->vm, this->font, *this->player);
}


//Constructors and Destructor:

PlayerGui::PlayerGui(Player* player, sf::VideoMode& video_mode)
	: vm(video_mode)
{
	this->player = player;

	this->initFont(this->font, "Fonts/Dosis-Light.ttf");
	this->initHpBar();
	this->initLevelBar();
	this->initExpBar();
	this->initPlayerTabPanel();
}

PlayerGui::~PlayerGui()
{
	// Deleting hp bar
	delete this->hpBar;

	// Deleting exp bar
	delete this->expBar;

	// Deleting player tab panel
	delete this->playerTabs;
}


// Accessors:

const bool PlayerGui::isTabsOpen() const
{
	return this->playerTabs->isOpen();
}


//FUnctions:

void PlayerGui::toggleCharacterTab()
{
	this->playerTabs->toggleCharacterTab();
}

void PlayerGui::updateHpBar(const float& dt)
{
	this->hpBar->update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax, dt, true);
}

void PlayerGui::updateLevelBar(const float& dt)
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGui::updateExpBar(const float& dt)
{
	this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext, dt);
}

void PlayerGui::updatePlayerTabPanel(const float& dt)
{
	this->playerTabs->update(dt);
}

void PlayerGui::update(const float& dt)
{
	this->updateHpBar(dt);
	this->updateExpBar(dt);
	this->updateLevelBar(dt);
	this->updatePlayerTabPanel(dt);
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}

void PlayerGui::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGui::renderExpBar(sf::RenderTarget& target)
{
	this->expBar->render(target);
}

void PlayerGui::renderPlayerTabPanel(sf::RenderTarget& target)
{
	this->playerTabs->render(target);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderLevelBar(target);
	this->renderExpBar(target);
	this->renderPlayerTabPanel(target);
}