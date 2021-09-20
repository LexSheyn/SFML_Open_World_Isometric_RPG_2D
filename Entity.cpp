#include "stdafx.h"
#include "Entity.h"

//private: Functions:

void Entity::initVariables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->attributeComponent = nullptr;
	this->skillComponent = nullptr;
	this->directionComponent = nullptr;
	this->visionComponent = nullptr;

	this->expReward = 0;
}

//Constructors and Destructor:

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
	delete this->directionComponent;
	delete this->visionComponent;
}

//Component functions:

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, max_velocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const int level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{
	this->skillComponent = new SkillComponent();
}

void Entity::createDirectionComponent(sf::Vector2f direction_vector)
{
	this->directionComponent = new DirectionComponent(direction_vector);
}

void Entity::createVisionComponent(sf::Vector2f position, const float range, sf::Vector2f direction)
{
	this->visionComponent = new VisionComponent(position, range, direction);
}

//Accessors:

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPosition();
	}

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPosition() + 
			sf::Vector2f
			(
				this->hitboxComponent->getGlobalBounds().width / 2.f, 
				this->hitboxComponent->getGlobalBounds().height / 2.f
			);
	}

	return this->sprite.getPosition() + 
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f, 
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::Vector2i Entity::getGridPosition(const int grid_size_i) const
{
	if (this->hitboxComponent)
	{
		return sf::Vector2i
		(
			static_cast<int>(this->hitboxComponent->getPosition().x) / grid_size_i,
			static_cast<int>(this->hitboxComponent->getPosition().y) / grid_size_i
		);
	}

	return sf::Vector2i
	(
		static_cast<int>(this->sprite.getPosition().x) / grid_size_i,
		static_cast<int>(this->sprite.getPosition().y) / grid_size_i
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getGlobalBounds();
	}

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}

	//Error
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const float Entity::getDistance(const Entity& entity) const
{
	return static_cast<float>(std::sqrt(std::pow((this->getCenter().x - entity.getCenter().x), 2) + std::pow((this->getCenter().y - entity.getCenter().y), 2)));
}

const AttributeComponent* Entity::getAttributeComponent() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent;
	}
	else
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className <<"::getAttributeComponent::Component has not initialized" << std::endl;
		return nullptr;
	}
}

VisionComponent* Entity::getVisionComponent() const
{
	if (this->visionComponent)
	{
		return this->visionComponent;
	}
	else
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::getVisionConponent::Component has not initialized" << std::endl;
		return nullptr;
	}
}

const bool Entity::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	std::string className = typeid(*this).name();
	className.erase(0, 6);
	std::cout << "ERROR::" << className << "::isDead::Attribute component and HP required" << std::endl;

	return false;
}

const int& Entity::getExpReward() const
{
	return this->expReward;
}

//Modifiers:

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->setPosition(x, y);
	}
	else
	{
		this->sprite.setPosition(x, y);
	}
}

void Entity::loseHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHp(hp);
	}	
}

void Entity::gainHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->gainHp(hp);
	}	
}

void Entity::loseExp(const int exp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseExp(exp);
	}	
}

void Entity::gainExp(const int exp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->gainExp(exp);
	}	
}

//Functions:

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		//Sets velocity
		this->movementComponent->move(dir_x, dir_y, dt);
	}

	if (this->skillComponent)
	{
		skillComponent->gainExp(SKILLS::ENDURANCE, 1);
	//	std::cout << "Endurance level: " << this->skillComponent->getSkillLevel(SKILLS::ENDURANCE) << std::endl;
	}
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocity();
	}
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityY();
	}
}
