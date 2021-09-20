#pragma once
class HitboxComponent
{
private:

//variables:

	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:

//Constructors and Destructor:

	HitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
	virtual ~HitboxComponent();

//Accessors:

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

//Modifiers:

	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

//Functions:

	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target, const bool visible = true);
};

