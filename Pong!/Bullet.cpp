#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos, sf::Vector2f faceDir, float speed)
{
	this->objectType = objectList::bullet;
	float mag = (float)sqrt(pow(faceDir.x, 2.f) + pow(faceDir.y, 2.f));
	sf::Vector2f unitDir = faceDir / mag;
	this->dir = unitDir;
	this->circle.setRadius(5.f);
	setLocation(pos + this->dir * 50.0f);
	this->speed = speed;
}

Bullet::~Bullet()
{
}

void Bullet::update(const float& dt)
{
	this->slide(dt);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->circle);
}

void Bullet::slide(const float& dt)
{
	this->circle.move(this->dir * dt * this->speed);
}