#ifndef BAR_H
#define BAR_H
#include "State.h"
class Ball;
class Bar
{
public:
	Bar(Ball* ball);
	Bar() = default;
	virtual ~Bar();

	//Functions
	void update(const float& dt, sf::Vector2i mPos);
	void render(sf::RenderTarget* target);
	void move(const float& dt, const float y);
	void setPosition(float x, float y);
	void playerMoving(const float& dt, sf::Vector2i mPos);
	bool intersects(const sf::CircleShape& c, const sf::RectangleShape& r);
	bool contains(const sf::CircleShape& c, const sf::Vector2f& p);
	void checkCollision();
	//Power up function
	void getWider();
	void addScore();
	
	sf::Vector2f getPosition();
	float getWidth();
	float getLength();
	int mode;
	float lLimit;
	float rLimit;
	Ball* ball;
	int score;
protected:
	sf::RectangleShape shape;
	sf::Color idleColor;
	sf::Color activeColor;
	float movementSpeed;
	float width;
	float length;
	sf::Font font;
	sf::Text text;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

#endif