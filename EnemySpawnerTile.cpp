#include "stdafx.h"
#include "EnemySpawnerTile.h"

//Constructors and Destructor:

EnemySpawnerTile::EnemySpawnerTile
(
	int grid_x, int grid_y, float grid_size_f,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, int32_t enemy_time_to_spawn, float enemy_distance_max
)
	: Tile(static_cast<int>(TileTypes::EnemySpawner), grid_x, grid_y, grid_size_f, texture, texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyDistanceMax = enemy_distance_max;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
	
}


//Accessors:

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top
		<< " " << this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyDistanceMax;

	return ss.str();
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}

const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}

const bool EnemySpawnerTile::canSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn
		&& this->enemyCounter < this->enemyAmount)
	{
		return true;
	}

	return false;
}


//Modifiers:

void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}


//Functions:

void EnemySpawnerTile::increaseEnemyCounter()
{
	++this->enemyCounter;

	if (this->enemyCounter > this->enemyAmount)
	{
		this->enemyCounter = this->enemyAmount;
	}
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	--this->enemyCounter;

	if (this->enemyCounter < 0)
	{
		this->enemyCounter = 0;
	}
}

void EnemySpawnerTile::update(const float& dt)
{
	if (this->canSpawn())
	{
		this->spawned = false;
	}
}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
