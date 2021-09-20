#pragma once

#include "Tile.h"

class Tile;

class EnemySpawnerTile :
	public Tile
{
private:

//Variables:

	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	int32_t enemyTimeToSpawn; // Milliseconds
	float enemyDistanceMax;
	
	bool spawned;

public:

//Constructors and Destructor:

	EnemySpawnerTile
	(
		int grid_x, int grid_y, float grid_size_f,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_type, int enemy_amount, int32_t enemy_time_to_spawn, float enemy_distance_max
	);
	virtual ~EnemySpawnerTile();

//Accessors:

	const std::string getAsString() const;
	const bool& getSpawned() const;
	const int& getEnemyCounter() const;
	const int& getEnemyAmount() const;
	const bool canSpawn() const;

//Modifiers:

	void setSpawned(const bool spawned);

//Functions:

	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f());
};

