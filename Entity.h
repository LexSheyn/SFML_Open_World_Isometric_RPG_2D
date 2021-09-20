#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "DirectionComponent.h"
#include "VisionComponent.h"

namespace Textures
{
	//Max number of texture sheets for each entity, change if required.
	const int indexMax = 60;
	
	/*
	enum class Players
	{
		PlayerOne = 0,
		PlayerTwo
	};

	enum class Enemies
	{
		Rat = 0,
		Fly
	};

	enum class Bosses
	{
		BossOne = 0,
		BossTwo
	};

	enum class TextureSheets
	{
		Idle = 0,
		Move,
		Attack,
		DodgeRoll,
		Dash,
		Skill,
		Death
	};

	enum class Animations
	{
		Idle_Left = 0,
		Idle_Left_Up,
		Idle_Left_Down,
		Idle_Right,
		Idle_Right_Up,
		Idle_Right_Down,
		Idle_Up,
		Idle_Down
	};
	*/

	namespace Players
	{
		enum PlayerOne
		{
			Idle_Down_Left = 0,
			Idle_Down_Right,
			Idle_Down,
			Idle_Up_Left,
			Idle_Up_Right,
			Idle_Up,
			Idle_Left,
			Idle_Right,
			PLAYER_MAX = Textures::indexMax - 1
		};
	}

	namespace Enemies
	{
		namespace Rats
		{
			enum Rat
			{
				Idle_Down_Left = Textures::indexMax,
				Idle_Down_Right,
				Idle_Down,
				Idle_Up_Left,
				Idle_Up_Right,
				Idle_Up,
				Idle_Left,
				Idle_Right,
				RAT_MAX = (Textures::indexMax * 2) - 1
			};
		}

		namespace Flyes
		{
			enum Fly
			{
				Idle_Down_Left = Textures::indexMax * 2,
				Idle_Down_Right,
				Idle_Down,
				Idle_Up_Left,
				Idle_Up_Right,
				Idle_Up,
				Idle_Left,
				Idle_Right,
				FLY_MAX = (Textures::indexMax * 3) - 1
			};
		}
	}
}

class Entity
{
private:

//private: Functions:

	void initVariables();

protected:

	//sf::Texture* texture;
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;
	DirectionComponent* directionComponent;
	VisionComponent* visionComponent;

	int expReward;

public:

//Constructors and Destructor:

	Entity();
	virtual ~Entity();

//Component functions:

	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float max_velocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const int level);
	void createSkillComponent();
	void createDirectionComponent(sf::Vector2f direction_vector);
	void createVisionComponent(sf::Vector2f position, const float range, sf::Vector2f direction);

//Accessors:

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f getCenter() const;
	const sf::Vector2i getGridPosition(const int grid_size_i) const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect getNextPositionBounds(const float& dt) const;
	const float getDistance(const Entity& entity) const;
	const AttributeComponent* getAttributeComponent() const;
	VisionComponent* getVisionComponent() const;
	const bool isDead() const;
	const int& getExpReward() const;

//Modifiers:

	void setPosition(const float x, const float y);
	void loseHp(const int hp);
	void gainHp(const int hp);
	void loseExp(const int exp);
	void gainExp(const int exp);

//Functions:
	
	void move(const float dir_x, const float dir_y, const float& dt);
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	virtual void update(const float& dt, sf::Vector2f& mouse_position_view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f shader_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

