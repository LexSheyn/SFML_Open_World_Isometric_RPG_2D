#pragma once

namespace MovementStates
{
	enum State
	{
		Idle = 0,
		Moving,
		Left,
		Right,
		Up,
		Down,
		UpRight,
		UpLeft,
		DownRight,
		DownLeft
	};
}

enum VelocityTypes : unsigned int
{
	Default = 0,
	Angular,
	Temporary
};

class MovementComponent
{
private:

//Variables:

	sf::Sprite& sprite;

	float pi;

	float velocityMax[3];

	float acceleration[3];

	float deceleration[3];

	sf::Vector2f velocity;

public:

//Constructors and Destructor:

	MovementComponent(sf::Sprite& sprite, float velocity_max, float acceleration, float deceleration);
	virtual ~MovementComponent();

//Accessors:

	const float& getVelocityMax() const;
	const sf::Vector2f& getVelocity() const;

//Functions:

	const bool getState(const short unsigned state)const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

