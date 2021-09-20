#include "stdafx.h"
#include "Rat.h"

// private: Functions:

void Rat::initVariables()
{

}

void Rat::initAnimations()
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

	this->animationComponent->addAnimation("IDLE_DOWN", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);

//	this->animationComponent->addAnimation("IDLE_DOWN", 15.f, 0, 0, 8, 0, 64, 64);
//	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
//	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
//	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
//	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
//	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void Rat::initGui()
{
	this->hpBar = new gui::ProgressBar(this->getPosition().x, this->getPosition().y, 40.f, 4.f);
	this->hpBar->setInnerTexture("Resources/Images/GUI/Player/health_bar.png");
	this->hpBar->setBackColor(sf::Color::Black);
}


// Conctructors and Destructor:

Rat::Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();
	this->initGui();

	//Components initialization
	this->createHitboxComponent(this->sprite, 60.f * 0.2f, 64.f * 0.3f, 60.f * 0.6f, 64.f * 0.7f);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(10);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);

	this->initAnimations();
}

Rat::~Rat()
{
	// Deleting gui
	delete this->hpBar;
}


// Accessors:



// Functions:

void Rat::updateGui(const float& dt)
{
	this->hpBar->setPosition(this->getPosition());
	this->hpBar->update(this->getAttributeComponent()->hp, this->getAttributeComponent()->hpMax, dt);
}

void Rat::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(MovementStates::State::Idle))
	{
		this->animationComponent->play("IDLE_DOWN", dt);
	}
	else if (this->movementComponent->getState(MovementStates::State::Left))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getVelocityMax());
	}
	else if (this->movementComponent->getState(MovementStates::State::Right))
	{
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

void Rat::update(const float& dt, sf::Vector2f& mouse_position_view)
{
	this->movementComponent->update(dt);

	this->updateGui(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->attributeComponent->update();
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f shader_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", shader_position);

		target.draw(this->sprite, shader);

		// Gui
		if (this->getAttributeComponent()->hp < this->getAttributeComponent()->hpMax)
		{
			this->hpBar->render(target);
		}
	}
	else
	{
		target.draw(this->sprite);

		// Gui
		if (this->getAttributeComponent()->hp < this->getAttributeComponent()->hpMax)
		{
			this->hpBar->render(target);
		}
	}

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}