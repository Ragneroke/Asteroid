#ifndef POWER_H
#define POWER_H
#include "State.h"
class Bar;
class Power
{
public:
	Power(float x, float y, Bar* player);
	Power() = default;
	virtual ~Power();
	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void checkCollision();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	const bool& getQuit() const;
	const bool& getActive() const;
	bool isActive = false;
	void turnActive();
private:
	int type = 0;
	Bar* player;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Texture texture;
	sf::Sprite shape;
	float width;
	float length;
	bool isDead;
	float speed;
};

#endif