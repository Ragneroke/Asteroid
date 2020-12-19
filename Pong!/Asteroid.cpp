#include "Asteroid.h"

Asteroid::Asteroid(int index, float baseSpeed)
{
	this->objectType = objectList::asteroid;
	this->asIndex = index;
	setRadiusOrigin(this->radiusArray[asIndex]);
	this->speed = rand() % 320 + baseSpeed;
	int startAngle = rand() % 360;
	this->dir = sf::Vector2f(cos(startAngle * 3.1415f / 180.f), sin(startAngle * 3.1415f / 180.f));
	this->randomPos();
	if (!this->texture.loadFromFile("Resource/asteroid.png")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->texture.setSmooth(true);
	this->texture.setRepeated(true);
	this->circle.setTexture(&this->texture);
}

Asteroid::Asteroid(int index, sf::Vector2f location, float baseSpeed)
{
	this->objectType = objectList::asteroid;
	this->asIndex = index;
	setRadiusOrigin(this->radiusArray[asIndex]);
	this->speed = rand() % 320 + baseSpeed;
	int startAngle = rand() % 360;
	this->dir = sf::Vector2f(cos(startAngle * 3.1415f / 180.f), sin(startAngle * 3.1415f / 180.f));
	setLocation(location);
	if (!this->texture.loadFromFile("Resource/asteroid.png")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->texture.setSmooth(true);
	this->texture.setRepeated(true);
	this->circle.setTexture(&this->texture);
}

void Asteroid::randomPos()
{
	float x = (float) (rand() % 800);
	float y = (float) (rand() % 600);
	setLocation(sf::Vector2f(x, y));
}

void Asteroid::update(const float& dt)
{
	slide(dt);
}

void Asteroid::render(sf::RenderTarget* target)
{
	if (!this->texture.loadFromFile("Resource/asteroid.png")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->circle.setTexture(&this->texture);
	target->draw(this->circle);
}

void Asteroid::slide(const float& dt)
{
	sf::Vector2f dest = getPosition() + this->dir * dt * this->speed;
	setLocation(dest);
}

void Asteroid::bounce(sf::Vector2f newDir)
{
	this->dir = newDir;
}

void Asteroid::setIndex(int index)
{

}
