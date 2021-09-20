#include "stdafx.h"
#include "EnemySystem.h"

//Constructors and Destructor:

EnemySystem::EnemySystem(std::vector<Enemy*>& active_enemies, std::map<const int, sf::Texture>& textures)
	: activeEnemies(active_enemies), textures(textures)
{
	
}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const int& type, const float& x, const float& y, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTypes::Type::Rat:

		this->activeEnemies.push_back(new Rat(x, y, textures[Textures::Enemies::Rats::Rat::Idle_Down], enemy_spawner_tile));
		
		enemy_spawner_tile.increaseEnemyCounter();
		
		break;
	
	default:

		std::cout << "ERROR::EnemySystem::createEnemy::Enemy type doesn't exist: " << type << std::endl;
		
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();

	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget* target)
{
}
