#include "stdafx.h"
#include "Player.h"

//Initialization functions:

void Player::initVariables()
{
	this->attacking = false;
	this->sword = new Sword(1, 10, 20, 100.f, 20, "Resources/Images/Sprites/Player/sword.png");
	this->sword->generate(10, 10);
}

void Player::initAnimations()
{
/*
this->animationComponent->addAnimation
(
	"IDLE_LEFT", //Animation name
	25.f, //Animation time
	0, //X first frame number, starts form 0
	0, //Y first frame number, starts from 0
	3, //X last frame number, starts form 0
	0, //Y last frame number, starts from 0
	58, //Width
	96 //Height
);
*/
	this->animationComponent->addAnimation("IDLE_DOWN", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void Player::initInventory()
{
	this->inventory = new Inventory(100);

	std::cout << "Inventory size before: " << this->inventory->getSize() << " / " << this->inventory->getSizeMax() << std::endl;

	//	this->inventory->add(&Sword(20)); // Does't work, requires a pointer to an already existing object.
	this->inventory->add(this->sword);

	this->inventory->remove(0);

	std::cout << "Inventory size after: " << this->inventory->getSize() << " / " << this->inventory->getSizeMax() << std::endl;
}

//Comstructors amd Destructor:

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	//Components initialization
	this->createHitboxComponent(this->sprite, 64.f * 0.2f, 64.f * 0.3f, 64.f * 0.6f, 64.f * 0.7f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();
	this->createDirectionComponent(this->movementComponent->getVelocity());
	this->createVisionComponent(this->getCenter(), this->movementComponent->getVelocityMax(), this->directionComponent->getDirectionVector());

	this->setPosition(x, y);
	this->initAnimations();

	this->initInventory();
}

Player::~Player()
{
	//Deleting sword
	delete this->sword;

	//Deleting inventory
	delete this->inventory;
}

//Accessors:

Weapon* Player::getWeapon() const
{
	return this->sword;
}

//Functions:

void Player::playAnimation(std::string key, const float& dt, bool priority)
{
	this->animationComponent->play(key, dt, priority);
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		
	}

	if (this->movementComponent->getState(MovementStates::State::Idle))
	{
		this->animationComponent->play("IDLE_DOWN", dt);
	}
	else if (this->movementComponent->getState(MovementStates::State::Left))
	{
		//Mirroring anination mechanics:
		//	if (this->sprite.getScale().x < 0.f)
		//	{
		//		this->sprite.setOrigin(0.f, 0.f);
		//		this->sprite.setScale(1.f, 1.f);
		//	}
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getVelocityMax());
	}
	else if (this->movementComponent->getState(MovementStates::State::Right))
	{
		//Mirroring anination mechanics:
		//	if (this->sprite.getScale().x > 0.f)
		//	{
		//		this->sprite.setOrigin(58.f, 0.f);
		//		this->sprite.setScale(-1.f, 1.f);
		//	}
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getVelocityMax());
	}
	else if (this->movementComponent->getState(MovementStates::State::Up))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getVelocityMax());
	}
	else if (this->movementComponent->getState(MovementStates::State::Down))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getVelocityMax());
	}
}

void Player::update(const float& dt, sf::Vector2f& mouse_position_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->sword->update(mouse_position_view, this->getCenter());
	
	this->directionComponent->update(this->movementComponent->getVelocity());
//	this->directionComponent->update(mouse_position_view - this->getCenter());
	this->visionComponent->update(this->getCenter(), this->directionComponent->getDirectionVector(), dt);
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f shader_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", shader_position);

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", shader_position);
	
		this->sword->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->sword->render(target);
	}

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}

//	sf::CircleShape circle;
//	circle.setRadius(2.f);
//	circle.setPosition
//	(
//		this->visionComponent->getDirection().x + this->getCenter().x, 
//		this->visionComponent->getDirection().y + this->getCenter().y
//	);
//	circle.setFillColor(sf::Color::Yellow);
//	target.draw(circle);
}
