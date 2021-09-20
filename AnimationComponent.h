#pragma once
class AnimationComponent
{
private:

//Animation class:

	class Animation
	{
	public:

	//Variables:

		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

	//Constructors:

		Animation
		(
			sf::Sprite& sprite, sf::Texture& textureSheet, 
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
		)
			: sprite(sprite), textureSheet(textureSheet), 
			animationTimer(animation_timer), timer(animation_timer), done(false),
			width(width), height(height)
		{
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

	//Accessors:

		const bool& isDone() const
		{
			return this->done;
		}

	//Functions:

		const bool& play(const float& dt)
		{
			//Updating timer
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//Resetting timer
				this->timer = 0.f;

				//Animating
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Resetting animation
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}				

				this->sprite.setTextureRect(this->currentRect);
			}

			return this->done;
		}

		const bool& play(float mod_percent, const float& dt)
		{
			//Updating timer
			if (mod_percent < 0.8f)
			{
				mod_percent = 0.8f;
			}
			this->done = false;
			this->timer += mod_percent * 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//Resetting timer
				this->timer = 0.f;

				//Animating
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Resetting animation
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}

			return this->done;
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};

//Variables:

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:

//Constructors and Destructor:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

//Accessors:

	const bool& isDone(const std::string key);

//Functions:

	void addAnimation
	(
		const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
	);

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

