#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>
class GameObject
{
protected:
	sf::CircleShape circle;
	float angle;

public:
	int index;
	enum objectList{ ship, bullet, asteroid, powerUp};
	objectList objectType;
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	GameObject();
	float getCurAngle();
	float getRadius();
	void setLocation(sf::Vector2f dest);
	void setRadiusOrigin(float radius);
	void setRotation(float dAngle);
	sf::Vector2f getPosition();

};

#endif