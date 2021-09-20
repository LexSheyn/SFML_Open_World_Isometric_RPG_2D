#pragma once

#include "EnemySpawnerTile.h"
#include "Rat.h"

namespace EnemyTypes
{
	enum Type
	{
		Rat = 0
	};
}

class EnemySystem
{
private:

	std::map<const int, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;

public:

//Constructors and Destructor:

	EnemySystem(std::vector<Enemy*>& active_enemies, std::map<const int, sf::Texture>& textures);
	virtual ~EnemySystem();

//Accessors:

	//

//Modifiers:

	//

//Functions:

	void createEnemy(const int& type, const float& x, const float& y, EnemySpawnerTile& enemy_spawner_tile);
	void removeEnemy(const int index);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

