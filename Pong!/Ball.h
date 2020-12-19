#ifndef BALL_H
#define BALL_H
#include "State.h"

class Ball
{
public:
	Ball();
	virtual ~Ball();
	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void initialBall();
	void resetPosition();
	void checkCollision();
	void checkMovement();
	void setPosition(float x, float y);
	void addScore();
	sf::Vector2f getPosition();
	sf::CircleShape getShape();
	int yDir = 0;
	int xDir = 0;
	int score = 0;
	int life = 3;
	bool isBhMode = false;
	bool isActive = false;
protected:
	sf::CircleShape shape;
	sf::Color idleColor;
	sf::Font font;
	sf::Text lifeText;
	sf::Text scoreText;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	float movementSpeed;
	float currentSpeed;
	float radius;
	float dx;
	float dy;
	float ody;

};


#endif