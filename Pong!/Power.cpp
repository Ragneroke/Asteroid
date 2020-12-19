#include "Power.h"

Power::Power(float x, float y, Bar* player)
{
	this->width = 40.f;
	this->length = 40.f;
	if (!this->texture.loadFromFile("Resource/bricks.png")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->texture.setSmooth(true);
	this->texture.setRepeated(true);
	//this->shape.setSize(sf::Vector2f(this->width, this->length));
	this->shape.setTexture(this->texture);
	this->shape.setTextureRect(sf::IntRect(0, 0, (int)this->width, (int)this->length));
	this->shape.setPosition(x, y);
	this->speed = 5.f;
	this->isDead = false;
	this->player = player;
}

Power::~Power()
{
}

void Power::update(const float& dt)
{
	if (!this->isDead and this->isActive) {
		this->shape.setTexture(this->texture);
		this->shape.move(0.f, this->speed);
		this->checkCollision();
	}
}

void Power::render(sf::RenderTarget* target)
{
	if(!this->isDead and this->isActive)
	target->draw(this->shape);
}

void Power::checkCollision()
{
	sf::Vector2f bPos = this->player->getPosition();
	sf::Vector2f pos = this->getPosition();
	if (pos.x + this->width > bPos.x 
		and pos.x < bPos.x + this->player->getWidth() 
		and pos.y + this->width > bPos.y 
		and pos.y < bPos.y + 10.f) {
		this->player->getWider();
		this->isDead = true;
		this->isActive = false;
	}

}

sf::Vector2f Power::getPosition()
{
	return this->shape.getPosition();
}

void Power::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

const bool& Power::getQuit() const
{
	return this->isDead;
}

const bool& Power::getActive() const
{
	return this->isActive;
}

void Power::turnActive()
{
	this->isActive = true;
}
