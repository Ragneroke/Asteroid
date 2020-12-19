#ifndef RECTS_H
#define RECTS_H
#include "State.h"
class Ball;
class Power;
class Rects
{
public:
	Rects(float x, float y, Ball* ball);
	Rects() = default;
	virtual ~Rects();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void checkCollision();
	void setPosition(float x, float y);
	const bool& getQuit() const;
	sf::Vector2f getPosition();
	Ball* ball;
protected:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Texture texture;
	sf::Sprite shape;
	float width;
	float length;
	bool isDead;

};


#endif