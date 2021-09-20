#pragma once

enum class TileTypes
{
	Default = 0,
	Damaging,
	Doodad,
	EnemySpawner,
	TILE_TYPES_MAX = EnemySpawner
	//And so on...
};

class Tile
{
private:



protected:

	sf::Sprite shape;
	int type;
	bool collision;

public:

//Constructors and Destructor:

	Tile();
	Tile
	(
		int type,
		int grid_x, int grid_y, float grid_size_f,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		const bool collision
	);
	virtual ~Tile();

//Accessors:

	const int& getType() const;
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;	

//Fuctions:

	const bool intersects(const sf::FloatRect bounds) const;
	
	virtual const std::string getAsString() const = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_position = sf::Vector2f()) = 0;
};

