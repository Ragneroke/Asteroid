#include "GameObject.h"
GameObject::GameObject() {

}

float GameObject::getCurAngle()
{
	return angle;
}

float GameObject::getRadius()
{
	return circle.getRadius();
}

void GameObject::setLocation(sf::Vector2f dest)
{
	float radius = getRadius();
	sf::Vector2f circleCenter = getPosition();
	sf::Vector2f screenDim = sf::Vector2f(800.f,600.f);
	if (circleCenter.x + radius < 0) {
		circle.setPosition(sf::Vector2f(screenDim.x + radius, circleCenter.y));
	}
	else if (circleCenter.x - radius > screenDim.x) {
		circle.setPosition(sf::Vector2f(0 - radius, circleCenter.y));
	}
	else if (circleCenter.y + radius < 0) {
		circle.setPosition(sf::Vector2f(circleCenter.x, screenDim.y + radius));
	}
	else if (circleCenter.y - radius > screenDim.y) {
		circle.setPosition(sf::Vector2f(circleCenter.x, 0 - radius));
	}
	else {
		circle.setPosition(dest);
	}
}

void GameObject::setRadiusOrigin(float radius)
{
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
}

void GameObject::setRotation(float dAngle)
{
	angle = dAngle;
	circle.setRotation(dAngle);
}

sf::Vector2f GameObject::getPosition()
{
	return circle.getPosition();
}

void GameObject::update(const float& dt)
{
}

void GameObject::render(sf::RenderTarget* target)
{
	target->draw(circle);
}
