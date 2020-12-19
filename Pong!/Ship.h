#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include <iostream>
#include <cmath>
class Ship : public GameObject
{
public:
	Ship(float x, float y);
	~Ship();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void checkCollision();
	void setPosition(float x, float y);
	const bool& getQuit() const; 
	sf::Vector2f getForward();

protected:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Texture texture;
	sf::CircleShape thrustAni;

	void turn(const float& dt);
	void slide(const float& dt);
	void trust(const float& dt);
	void drag(const float& dt);
	float width;
	float length;
	bool isDead;
	sf::Vector2f velocity;
	float fireCd;
	float speed;
	float maxAcc;
	float curAcc;
	float rps;
	float Cd;
	bool isThrusting = false;


};


#endif