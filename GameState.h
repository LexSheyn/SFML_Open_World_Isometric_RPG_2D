#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TextTagSystem.h"

class GameState :
    public State
{
private:

    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pauseMenu;

    sf::Shader core_shader;

    Player* player;
    PlayerGui* playerGui;

    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;

    TileMap* tileMap;

// Systems:

    TextTagSystem* textTagSystem;

// FPS counter:

    sf::Text fps;

//private: Functions

    void initDefferedRender();
    void initView();
    void initPauseMenu();
    void initShaders();
    void initPlayers();
    void initPlayerGui();
    void initEnemySystem();
    void initTileMap();
    void initSystems();
    void initSoundEngine();

public:

//Constructor and Destructor:

    GameState(StateData* state_data);
    virtual ~GameState();

//Functions:

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGui(const float& dt);
    void updatePauseMenuButtons();
    void uodateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void updateCombat(Enemy* enemy, const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

