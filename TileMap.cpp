#include "stdafx.h"
#include "TileMap.h"

//private: Functions:

//Clears the map.
void TileMap::clearMap()
{
	for (size_t x = 0; x < this->map.size(); x++)
	{
		for (size_t y = 0; y < this->map[x].size(); y++)
		{
			for (size_t z = 0; z < this->map[x][y].size(); z++)
			{
				for (size_t k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = nullptr;
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	std::cout << "TileMap::clearMap::Map size: " << this->map.size() << std::endl;
}

//Constructors and Destructor:

TileMap::TileMap(float grid_size, int width, int height, int layers, std::string texture_file_path)
{
	this->gridSizeF = grid_size;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * grid_size;
	this->maxSizeWorldF.y = static_cast<float>(height) * grid_size;
	this->layers = layers;
	this->textureFilePath = texture_file_path;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	//TEST
	if (!this->tileSheet.loadFromFile(texture_file_path))
	{
		std::cout << "ERROR::TileMap::TileMap::Failes to load grass texture " << texture_file_path << std::endl;
	}

	//DEBUG Collision box, change it later
	this->collisionBox.setSize(sf::Vector2f(grid_size, grid_size));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(-1.f);
}

//Should use '\\' instead of '/' in the file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
TileMap::TileMap(const std::string file_path)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_path);

	//DEBUG Collision box, change it later
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(-1.f);
}

TileMap::~TileMap()
{
	this->clearMap();
}

//Accessors:

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}

	return false;
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return static_cast<int>(this->map[x][y][layer].size());
			}
		}
	}

	//If no tiles
	return 0;
}

const int& TileMap::getLayer()
{
	return this->layer;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorldF;
}

const bool TileMap::checkType(const int x, const int y, const int z, const int type) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		if (!this->map[x][y][z].empty())
		{
			return this->map[x][y][z].back()->getType() == type;
		}
	}
	
	return false;
}

//Functions:

//Tekes three indices frpm the mouse position in the grid and adds a tile to that position,
//if the internal tilemap array allows it.
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const int type)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		//OK to add a tile
		this->map[x][y][z].push_back(new RegularTile(type, x, y, this->gridSizeF, this->tileSheet, texture_rect, collision));

		std::cout << "TileMap::addTile::Tile added." << std::endl;
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const int enemy_type, const int enemy_amount, const int32_t enemy_time_to_spawn, const float enemy_distance_max)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		//OK to add a tile
		this->map[x][y][z].push_back
		(
			new EnemySpawnerTile
			(
				x, y, this->gridSizeF, this->tileSheet, texture_rect, 
				enemy_type, enemy_amount, enemy_time_to_spawn, enemy_distance_max
			)
		);

		std::cout << "TileMap::addTile::Tile added." << std::endl;
	}
}

//Tekes three indices frpm the mouse position in the grid and removes a tile on that position,
//if the internal tilemap array allows it.
void TileMap::removeTile(const int x, const int y, const int z, const int type)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0
		&& y < this->maxSizeWorldGrid.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			//OK to remove
			if (type >= 0)
			{
				if (this->map[x][y][z].back()->getType() == type)
				{
					delete this->map[x][y][z].back();
					this->map[x][y][z].pop_back();
					std::cout << "TileMap::removeTile::Tile removed." << std::endl;
				}
			}
			else
			{
			//	delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				delete this->map[x][y][z].back();
				this->map[x][y][z].pop_back();
				std::cout << "TileMap::removeTile::Tile removed." << std::endl;
			}
		}
	}
}

//Saves the entire tilemap to a text file.
//Format:
// #### Map:
// - Size x y
// - Grid size
// - Layers
// - Texture file path
// #### Tiles:
// - Type, Grid X, Grid Y, Layer, Texture rect X, Texture rect Y, Collision
//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
void TileMap::saveToFile(const std::string file_path)
{
	std::ofstream out;

	out.open(file_path);

	if (out.is_open())
	{
		//Map:
		out << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << " " << this->layers << "\n";
		out << this->gridSizeI << "\n";
		out << this->textureFilePath << "\n";

		//Tiles:
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< " ";
						}
					}
				}
			}
		}
	}

	out.close();

	//Debug
	std::cout << "TileMap::saveToFile::Map saved" << std::endl;
}

//Should use '\\' instead of '/' in a file path and put this file to the .exe location,
//to be able to play the game without Visual Studio.
void TileMap::loadFromFile(const std::string file_path)
{
	std::ifstream in;

	in.open(file_path);

	if (in.fail())
	{
		std::cout << "ERROR::TileMap::loadFromFile::Failed to load " << file_path << std::endl;
	}
	else if (in.is_open())
	{
		sf::Vector2i size;
		int layers = 0;
		int grid_size = 0;
		std::string texture_file_path = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int texture_rect_x = 0;
		int texture_rect_y = 0;
		bool collision = false;
		int type = 0;

		//Map:
		in >> size.x >> size.y >> layers >> grid_size >> texture_file_path;

		//Clearing the map
		this->clearMap();

		//Tiles:
		this->gridSizeF = static_cast<float>(grid_size);
		this->gridSizeI = grid_size;

		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * grid_size);
		this->maxSizeWorldF.y = static_cast<float>(size.y * grid_size);
		this->layers = layers;
		this->textureFilePath = texture_file_path;

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		//Loading texture for tiles.
		//Should use '../' before the file path to be able to play the game without Visual Studio.
		if (!this->tileSheet.loadFromFile(texture_file_path))
		{
			std::cout << "ERROR::TileMap::TileMap::Failed to load grass texture " << texture_file_path << std::endl;
		}

		//Load all tiles
		while (in >> x >> y >> z >> type)
		{
			if (type != static_cast<int>(TileTypes::EnemySpawner))
			{
				in >> texture_rect_x >> texture_rect_y 
					>> collision;

				this->map[x][y][z].push_back
				(
					new RegularTile
					(
						type,
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(texture_rect_x, texture_rect_y, this->gridSizeI, this->gridSizeI),
						collision
					)
				);
			}
			else if (type == static_cast<int>(TileTypes::EnemySpawner))
			{
				int enemy_type = 0;
				int enemy_amount = 0;
				int32_t enemy_time_to_spawn = 0;
				float enemy_distance_max = 0.f;

				in >> texture_rect_x >> texture_rect_y
					>> enemy_type >> enemy_amount >> enemy_time_to_spawn >> enemy_distance_max;

				this->map[x][y][z].push_back
				(
					new EnemySpawnerTile
					(
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(texture_rect_x, texture_rect_y, this->gridSizeI, this->gridSizeI),
						enemy_type, enemy_amount, enemy_time_to_spawn, enemy_distance_max
					)
				);
			}
		}
	}

	in.close();

	//Debug	
	std::cout << "TileMap::loadFromFile::Map loaded" << std::endl;
	std::cout << "TileMap::loadFromFile::Map size: " << this->maxSizeWorldGrid.x << " x " << this->maxSizeWorldGrid.y << std::endl;
}

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
	//World bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{
	//Tiles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (!this->map[x][y][this->layer].empty())
				{
					sf::FloatRect player_bounds = entity->getGlobalBounds();
					sf::FloatRect wall_bounds = this->map[x][y][this->layer][k]->getGlobalBounds();
					sf::FloatRect next_position_bounds = entity->getNextPositionBounds(dt);

					if (this->map[x][y][this->layer][k]->getCollision() &&
						this->map[x][y][this->layer][k]->intersects(next_position_bounds))
					{
						//Bottom collision
						if (player_bounds.top < wall_bounds.top
							&& player_bounds.top + player_bounds.height < wall_bounds.top + wall_bounds.height
							&& player_bounds.left < wall_bounds.left + wall_bounds.width
							&& player_bounds.left + player_bounds.width > wall_bounds.left)
						{
							entity->stopVelocityY();
							entity->setPosition(player_bounds.left, wall_bounds.top - player_bounds.height);
						}//Bottom collision				
						else if (player_bounds.top > wall_bounds.top
							&& player_bounds.top + player_bounds.height > wall_bounds.top + wall_bounds.height
							&& player_bounds.left < wall_bounds.left + wall_bounds.width
							&& player_bounds.left + player_bounds.width > wall_bounds.left)
						{
							entity->stopVelocityY();
							entity->setPosition(player_bounds.left, wall_bounds.top + wall_bounds.height);
						}

						//Right collision
						if (player_bounds.left < wall_bounds.left
							&& player_bounds.left + player_bounds.width < wall_bounds.left + wall_bounds.width
							&& player_bounds.top < wall_bounds.top + wall_bounds.height
							&& player_bounds.top + player_bounds.height > wall_bounds.top)
						{
							entity->stopVelocityX();
							entity->setPosition(wall_bounds.left - player_bounds.width, player_bounds.top);
						}//Left collision
						else if (player_bounds.left > wall_bounds.left
							&& player_bounds.left + player_bounds.width > wall_bounds.left + wall_bounds.width
							&& player_bounds.top < wall_bounds.top + wall_bounds.height
							&& player_bounds.top + player_bounds.height > wall_bounds.top)
						{
							entity->stopVelocityX();
							entity->setPosition(wall_bounds.left + wall_bounds.width, player_bounds.top);
						}
					}
				}
			}
		}
	}
}

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemy_system)
{
	//Tiles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 15;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = entity->getGridPosition(this->gridSizeI).x + 16;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}

	this->toY = entity->getGridPosition(this->gridSizeI).y + 9;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				// Updating tile
				if (!this->map[x][y][this->layer].empty())
				{
					this->map[x][y][this->layer][k]->update(dt);

					// Updating tile types (specific)
					if (this->map[x][y][this->layer][k]->getType() == static_cast<int>(TileTypes::EnemySpawner))
					{
						EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);
						if (es)
						{
							if (!es->getSpawned())// && es->getEnemyCounter() < es->getEnemyAmount())
							{
							//	enemy_system.createEnemy(EnemyTypes::Type::Rat, static_cast<float>(x) * this->gridSizeF, static_cast<float>(y) * this->gridSizeF);

								// TEST
								std::random_device seed;
								std::mt19937 random_damage(seed());
								std::uniform_int_distribution<int> generated(0, 600);

								enemy_system.createEnemy(EnemyTypes::Type::Rat, static_cast<float>(generated(random_damage)), static_cast<float>(generated(random_damage)), *es);
								es->setSpawned(true);
							}							
						}
					}
				}
			}
		}
	}
}

void TileMap::update(Entity* entity, const float& dt)
{

}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& grid_position, sf::Shader* shader, const sf::Vector2f player_position, const bool show_collision)
{

	this->layer = 0;

	this->fromX = grid_position.x - 15;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = grid_position.x + 16;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}

	this->fromY = grid_position.y - 8;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}

	this->toY = grid_position.y + 9;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (!this->map[x][y][this->layer].empty())
				{
					if (this->map[x][y][this->layer][k]->getType() == static_cast<int>(TileTypes::Doodad))
					{
						this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						if (shader)
						{
							this->map[x][y][this->layer][k]->render(target, shader, player_position);
						}
						else
						{
							this->map[x][y][this->layer][k]->render(target);
						}
					}
					
					if (show_collision)
					{
						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());

							target.draw(this->collisionBox);
						}
					}

					if (this->map[x][y][this->layer][k]->getType() == static_cast<int>(TileTypes::EnemySpawner))
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());

						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::renderDeffered(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	while (!this->defferedRenderStack.empty())
	{
		if (shader)
		{
			defferedRenderStack.top()->render(target, shader, player_position);
		}
		else
		{
			defferedRenderStack.top()->render(target);
		}
		defferedRenderStack.pop();
	}
}
