#include "stdafx.h"
#include "GameState.h"

//private: Functions

void GameState::initDefferedRender()
{
	this->renderTexture.create
	(
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect
	(
		sf::IntRect
		(
			0, 
			0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		//	1920.f,
		//	1080.f
		)
	);

	this->view.setCenter
	(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	//	1920.f / 2.f,
	//	1080.f / 2.f
	);
}

void GameState::initPauseMenu()
{
	const sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	this->pauseMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pauseMenu->addButton(gui::ButtonName::Resume, gui::percentIntoY(28.f, vm), gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm), gui::calculateCharSize(3.f, vm), "Resume");
	this->pauseMenu->addButton(gui::ButtonName::Settings, gui::percentIntoY(36.f, vm), gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm), gui::calculateCharSize(3.f, vm), "Settings");
	this->pauseMenu->addButton(gui::ButtonName::Quit, gui::percentIntoY(54.f, vm), gui::percentIntoX(12.f, vm), gui::percentIntoY(4.f, vm), gui::calculateCharSize(3.f, vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GameState::initShaders::Failed to load shaders" << std::endl;
	}
}

void GameState::initPlayers()
{
//	this->player = new Player(0.f, 0.f, this->textures["PLAYER_SHEET"]);
	this->player = new Player
	(
		gui::percentIntoX(10.f, this->stateData->gfxSettings->resolution), 
		gui::percentIntoY(20.f, this->stateData->gfxSettings->resolution),
	//	this->tileMap->getMaxSizeF().x / 5.f,
	//	this->tileMap->getMaxSizeF().y / 5.f,
		this->textures[Textures::Players::PlayerOne::Idle_Down]
	);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap()
{
//	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, 1, "Resources/Images/Tiles/tilesheet3.png");
//	this->tileMap->loadFromFile("Maps/test.tilemap");

	this->tileMap = new TileMap("Maps/test.tilemap");
}

void GameState::initSystems()
{
	this->textTagSystem = new TextTagSystem(this->stateData, "Fonts/slkscr.ttf");
}

void GameState::initSoundEngine()
{
	//Loading SFX files into RAM
	this->soundEngine.initSound(sfx::Sound::ButtonPress, "Resources/Sounds/ButtonPress.mp3");

	//Music files association initialization
//	this->soundEngine.initMusic(sfx::Music::Ambient, "Resources/Music/01. Dysphoria.mp3");
//	this->soundEngine.initMusic(sfx::Music::Ambient, "D:\\Royalty FREE Music\\NetLabels\\Ambient\\Raw Coffin\\Kultar\\Starvation\\07. Exhaustion.mp3");
//	this->soundEngine.initMusic(sfx::Music::Ambient, "D:/Royalty FREE Music/NetLabels/Ambient/Raw Coffin/Kultar/Starvation/07. Exhaustion.mp3");
}

//Constructors and Destructor:

GameState::GameState(StateData* state_data)
	: State(state_data)
{
//	std::thread t1(&GameState::initKeybinds, this, "Config/gamestate_keybinds.ini");
//	std::thread t2(&GameState::initFont, this, "Fonts/Dosis-Light.ttf");
//	std::thread t3(&GameState::initTexture, this, "PLAYER_SHEET", "Resources/Images/Sprites/Player/player_sans.png");
//	std::thread t4(&GameState::initPauseMenu, this);

	this->initDefferedRender();
	this->initView();
	this->initKeybinds("Config/gamestate_keybinds.ini");
	this->initFont(this->font, "Fonts/slkscr.ttf");
	this->initTexture(Textures::Players::PlayerOne::Idle_Down, "Resources/Images/Sprites/Player/PLAYER_SHEET2.png");
	this->initTexture(Textures::Enemies::Rats::Rat::Idle_Down, "Resources/Images/Sprites/Enemy/rat1_60x64.png");
//	this->initTexture(Textures::Enemies::Rats::Rat::Idle_Down, "Resources/Images/Sprites/Player/PLAYER_SHEET2.png");
	this->initPauseMenu();
	this->initShaders();

//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();

	this->initEnemySystem();
	this->initTileMap();
	this->initPlayers();
	this->initPlayerGui();
	this->initSystems();
	this->initSoundEngine();

// SOUND ENGINE TEST

	//Playing music TEST
//	this->soundEngine.playMusic(sfx::Music::Ambient, true, false);

//	std::cout << "Playing: " << this->soundEngine.isPlaying(sfx::Music::Ambient) << std::endl;
}

GameState::~GameState()
{
	//Deleting pause menu
	delete this->pauseMenu;

	//Deleting player
	delete this->player;

	//Deleting player GUI
	delete this->playerGui;

	//Deleting enemy system
	delete this->enemySystem;

	//Deleting tile map
	delete this->tileMap;

	// Deleting systems
	delete this->textTagSystem;

	//Deleting enemies
	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

//Functions:

void GameState::updateView(const float& dt)
{
	if (!this->playerGui->isTabsOpen())
	{
		this->view.setCenter
		(
			std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePositionWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
			std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePositionWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
		);
	}

	//Check for X
	if (this->view.getSize().x <= this->tileMap->getMaxSizeF().x)
	{
		if (this->view.getCenter().x - (this->view.getSize().x / 2.f) < 0.f)
		{
			this->view.setCenter(0.f + (this->view.getSize().x / 2.f), this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + (this->view.getSize().x / 2.f) > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - (this->view.getSize().x / 2.f), this->view.getCenter().y); //Get the map size eventually instead of 3000.f
		}
	}
	
	//Check for Y
	if (this->view.getSize().y <= this->tileMap->getMaxSizeF().y)
	{
		if (this->view.getCenter().y - (this->view.getSize().y / 2.f) < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + (this->view.getSize().y / 2.f));
		}
		else if (this->view.getCenter().y + (this->view.getSize().y / 2.f) > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - (this->view.getSize().y / 2.f)); //Get the map size eventually instead of 3000.f
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		//SOUND ENGINE TEST
		this->soundEngine.playSound(sfx::Sound::ButtonPress);

		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (!this->playerGui->isTabsOpen())
	{
		//Updating player input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) //Left
		{
			this->player->move(-1.f, 0.f, dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) //Right
		{
			this->player->move(1.f, 0.f, dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) //Up
		{
			this->player->move(0.f, -1.f, dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) //Down
		{
			this->player->move(0.f, 1.f, dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			this->player->loseHp(1);
			//SOUND ENGINE TEST
			this->soundEngine.increaseSfxVolume(-0.07f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			this->player->gainHp(1);
			//SOUND ENGINE TEST
			this->soundEngine.increaseSfxVolume(0.07f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			this->player->loseExp(1);
			//SOUND ENGINE TEST
			this->soundEngine.increaseMusicVolume(-0.07f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			this->player->gainExp(1);
			//SOUND ENGINE TEST
			this->soundEngine.increaseMusicVolume(0.07f);
		}
	}

//	//TEST
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) //Left
//	{
//		this->activeEnemies[0]->move(-1.f, 0.f, dt);
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) //Right
//	{
//		this->activeEnemies[0]->move(1.f, 0.f, dt);
//	}
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) //Up
//	{
//		this->activeEnemies[0]->move(0.f, -1.f, dt);
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) //Down
//	{
//		this->activeEnemies[0]->move(0.f, 1.f, dt);
//	}
}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB_CHARACTER"))) && this->getKeyTime())
	{
		this->playerGui->toggleCharacterTab();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed(gui::ButtonName::Resume))
	{
		this->paused = false;
		this->soundEngine.playSound(sfx::Sound::ButtonPress);
	}
	else if (this->pauseMenu->isButtonPressed(gui::ButtonName::Settings))
	{
		//
	}
	else if (this->pauseMenu->isButtonPressed(gui::ButtonName::Quit))
	{
		this->endState();
	}
}

void GameState::uodateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePositionView);
}

void GameState::updateEnemies(const float& dt)
{
	uint32_t index = 0;

	for (auto* enemy : this->activeEnemies)
	{		
		this->activeEnemies[index]->update(dt, this->mousePositionView);

		this->tileMap->updateWorldBoundsCollision(this->activeEnemies[index], dt);
		this->tileMap->updateTileCollision(this->activeEnemies[index], dt);

		this->updateCombat(this->activeEnemies[index], dt);

		if (this->activeEnemies[index]->isDead())
		{
			this->player->gainExp(this->activeEnemies[index]->getExpReward());

			this->textTagSystem->addTextTag(TagTypes::Experience, this->player->getPosition().x, this->player->getPosition().y, this->activeEnemies[index]->getExpReward(), "+", "exp");

			this->enemySystem->removeEnemy(index);

			--index;
		}
		else
		{
			// TEST
//			std::random_device seed_x;
//			std::mt19937 random_x(seed_x());
//			std::uniform_int_distribution<int> generated_x(-3, 3);
//
//			std::random_device seed_y;
//			std::mt19937 random_y(seed_y());
//			std::uniform_int_distribution<int> generated_y(-6, 6);
//
//			this->activeEnemies[index]->move(generated_x(random_x), generated_y(random_y), dt);
		//	this->activeEnemies[i]->move(1.f, 1.f, dt);
		}

		++index;
	}
}

void GameState::updateCombat(Enemy* enemy, const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (enemy->getGlobalBounds().contains(this->mousePositionView) 
			&& enemy->getDistance(*this->player) < this->player->getWeapon()->getRange()
			&& this->player->getWeapon()->getAttackTimer())
		{
			std::cout << "Hit! " << enemy->getDistance(*this->player) << std::endl;

			int damage = this->player->getWeapon()->getDamage();			
			enemy->loseHp(damage);
			this->textTagSystem->addTextTag(TagTypes::Negative, enemy->getPosition().x, enemy->getPosition().y, damage, "-", "hp");
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if (enemy->getGlobalBounds().contains(this->mousePositionView) 
			&& enemy->getDistance(*this->player) < this->player->getWeapon()->getRange()
			&& this->player->getWeapon()->getAttackTimer())
		{
			std::cout << "Heal! " << enemy->getDistance(*this->player) << std::endl;

			int damage = this->player->getWeapon()->getDamage();
			enemy->gainHp(damage);
			this->textTagSystem->addTextTag(TagTypes::Positive, enemy->getPosition().x, enemy->getPosition().y, damage, "+", "hp");
		}
	}
}

void GameState::update(const float& dt)
{	
	this->updateMousePositions(&this->view);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);
	
		this->uodateTileMap(dt);

		this->updatePlayer(dt);
		this->updatePlayerGui(dt);

		//Updating all enemies
		this->updateEnemies(dt);

		// Updating systems
		this->textTagSystem->update(dt);
	}
	else //Paused update
	{
		this->pauseMenu->update(this->mousePositionWindow, dt);
		this->updatePauseMenuButtons();
	}

	this->soundEngine.update(dt);

//Debug:

	this->updateFpsCounter(dt);
//	this->updateMousePositionText();
}

void GameState::render(sf::RenderTarget* target)
{
	// All to the window
	if (!target)
	{
		target = this->window;
	}

	this->renderTexture.clear();

	// Map
	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, this->viewGridPosition, &this->core_shader, this->player->getCenter(), false);
//	// TEST
//	if (this->player->getVisionComponent())
//	{
//		this->player->getVisionComponent()->render(this->renderTexture);
//	}
	// Enemy
	for (auto *enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}
	// Player
	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	//Deffered rendering
	this->tileMap->renderDeffered(this->renderTexture, &this->core_shader, this->player->getCenter());
	this->textTagSystem->render(this->renderTexture);

	// Player GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);

	// Pause menu render
	if (this->paused) 
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pauseMenu->render(this->renderTexture);
	}

	// Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	// TEST
	sf::Text SIZE;
	SIZE.setFont(this->font);
	SIZE.setString(std::to_string(this->activeEnemies.size()));
	SIZE.setPosition(400.f, 0.f);

	target->draw(SIZE);

//Debug:

	this->renderFpsCounter(target);
//	this->renderMousePositionText(target);
}
