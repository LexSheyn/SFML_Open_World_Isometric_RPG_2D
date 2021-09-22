#pragma once

#include "PlayerTabPanel.h"

class PlayerGui
{
private:

// Variables:

	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	// HP Bar
	gui::ProgressBar* hpBar;

	// Level Bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;
	sf::Texture levelBarTexture;

	// EXP Bar
	gui::ProgressBar* expBar;

	// Player tab panel
	PlayerTabPanel* playerTabs;

// private: Functions:

	void initFont(sf::Font& font_name, const std::string file_path);
	void initHpBar();
	void initLevelBar();
	void initExpBar();
	void initPlayerTabPanel();

public:

// Constructors and Destructor:

	PlayerGui(Player* player, sf::VideoMode& video_mode);
	virtual ~PlayerGui();

// Accessors:

	const bool isTabsOpen() const;

// Fucntions:

	void toggleCharacterTab();

	void updateHpBar(const float& dt);
	void updateLevelBar(const float& dt);
	void updateExpBar(const float& dt);
	void updatePlayerTabPanel(const float& dt);

	void update(const float& dt);

	void renderHpBar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderPlayerTabPanel(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

