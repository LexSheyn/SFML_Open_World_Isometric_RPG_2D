#include "stdafx.h"
#include "Enemy.h"

//Comstructors amd Destructor:

//Enemy::Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet)
//	: enemySpawner(enemy_spawner)
Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	: enemySpawnerTile(enemy_spawner_tile)
{
	this->expReward = 100;
}

Enemy::~Enemy()
{

}


//Accessors:

EnemySpawnerTile& Enemy::getEnemySpawnerTile() const
{
	return this->enemySpawnerTile;
}

//Functions:

void Enemy::generateAttributes(const int level)
{
	this->expReward = level * 10 + (std::rand() % (level)+1);
}

void Enemy::playAnimation(std::string key, const float& dt, bool priority)
{
	this->animationComponent->play(key, dt, priority);
}