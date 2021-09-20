#include "stdafx.h"
#include "MovementComponent.h"

//Constructors and Destructor:

MovementComponent::MovementComponent(sf::Sprite& sprite, float velocity_max, float acceleration, float deceleration)
	: sprite(sprite)
{
	this->pi = 3.141592f;

	// std::cos((45.f * this->pi) / 180.f) = 0.707107f;

	// Default
	this->velocityMax[Default] = velocity_max;
	this->acceleration[Default] = acceleration;
	this->deceleration[Default] = deceleration;

	// Angular
	this->velocityMax[Angular] = this->velocityMax[Default] * 0.707107f;
	this->acceleration[Angular] = this->acceleration[Default] * 0.707107f;
	this->deceleration[Angular] = this->deceleration[Default] * 0.707107f;

	// Temporary
	this->velocityMax[Temporary] = this->velocityMax[Default];
	this->acceleration[Temporary] = this->acceleration[Default];
	this->deceleration[Temporary] = this->deceleration[Default];
}

MovementComponent::~MovementComponent()
{

}

//Accessors:

const float& MovementComponent::getVelocityMax() const
{
	return this->velocityMax[Default];
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}


//Functions:

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case MovementStates::State::Idle:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			return true;
		}
		break;

	case MovementStates::State::Moving:

		if (this->velocity.x != 0.f && this->velocity.y != 0.f)
		{
			return true;
		}
		break;

	case MovementStates::State::Left:

		if (this->velocity.x < 0.f)
		{
			return true;
		}
		break;

	case MovementStates::State::Right:

		if (this->velocity.x > 0.f)
		{
			return true;
		}
		break;

	case MovementStates::State::Up:

		if (this->velocity.y < 0.f)
		{
			return true;
		}
		break;

	case MovementStates::State::Down:

		if (this->velocity.y > 0.f)
		{
			return true;
		}
		break;
	}

	return false;
}

//Resets the velocity to 0.
void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

//Resets the velocity X to 0.
void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

//Resets the velocity Y to 0.
void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

//Accelerates the sprite until it reaches the max velocity.
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration X
	this->velocity.x += this->acceleration[Temporary] * dir_x * dt;

	//Acceleration Y
	this->velocity.y += this->acceleration[Temporary] * dir_y * dt;

}

//Decelerates the sprite and controls the maximum velocity.
//Corrects the moves with using Delta Time (dt).
void MovementComponent::update(const float& dt)
{
	if (this->velocity.x != 0.f && this->velocity.y != 0.f)
	{
		velocityMax[Temporary] = this->velocityMax[Angular];
		acceleration[Temporary] = this->acceleration[Angular];
		deceleration[Temporary] = this->deceleration[Angular];
	}
	else
	{
		velocityMax[Temporary] = this->velocityMax[Default];
		acceleration[Temporary] = this->acceleration[Default];
		deceleration[Temporary] = this->deceleration[Default];
	}

	// X:
	if (this->velocity.x > 0) //Check for right
	{
		//Max velocity check positive
		if (this->velocity.x > velocityMax[Temporary])
		{
			this->velocity.x = velocityMax[Temporary];
		}

		//Deceleration positive
		this->velocity.x -= deceleration[Temporary] * dt;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0) //Check for left
	{
		//Max velocity check negative
		if (this->velocity.x < -velocityMax[Temporary])
		{
			this->velocity.x = -velocityMax[Temporary];
		}

		//Deceleration negative
		this->velocity.x += deceleration[Temporary] * dt;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	// Y:
	if (this->velocity.y > 0) //Check for Down
	{
		//Max velocity check positive
		if (this->velocity.y > velocityMax[Temporary])
		{
			this->velocity.y = velocityMax[Temporary];
		}

		//Deceleration positive
		this->velocity.y -= deceleration[Temporary] * dt;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0) //Check for Up
	{
		//Max velocity check negative
		if (this->velocity.y < -velocityMax[Temporary])
		{
			this->velocity.y = -velocityMax[Temporary];
		}

		//Deceleration negative
		this->velocity.y += deceleration[Temporary] * dt;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}

	/*
	// X:
	if (this->velocity.x > 0) //Check for right
	{
		//Max velocity check positive
		if (this->velocity.x > this->velocityMax)
		{
			this->velocity.x = this->velocityMax;
		}

		//Deceleration positive
		this->velocity.x -= this->deceleration * dt;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0) //Check for left
	{
		//Max velocity check negative
		if (this->velocity.x < -this->velocityMax)
		{
			this->velocity.x = -this->velocityMax;
		}

		//Deceleration negative
		this->velocity.x += this->deceleration * dt;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	// Y:
	if (this->velocity.y > 0) //Check for Down
	{
		//Max velocity check positive
		if (this->velocity.y > this->velocityMax)
		{
			this->velocity.y = this->velocityMax;
		}

		//Deceleration positive
		this->velocity.y -= this->deceleration * dt;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0) //Check for Up
	{
		//Max velocity check negative
		if (this->velocity.y < -this->velocityMax)
		{
			this->velocity.y = -this->velocityMax;
		}

		//Deceleration negative
		this->velocity.y += this->deceleration * dt;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	*/

//	//Final move
	this->sprite.move(this->velocity * dt);
}
