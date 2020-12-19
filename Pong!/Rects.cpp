#include "Rects.h"

Rects::Rects(float x, float y, Ball* ball)
{
	this->width = 80.f;
	this->length = 20.f;
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
	this->ball = ball;
	this->isDead = false;
	if (!buffer.loadFromFile("Resource/crash.wav")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->sound.setBuffer(buffer);
}

Rects::~Rects()
{

}

void Rects::update(const float& dt)
{
	if (!this->isDead) {
		this->checkCollision(); 
	}
}

void Rects::render(sf::RenderTarget* target)
{
	if (!this->isDead) {
		
		this->shape.setTexture(this->texture);
		
		target->draw(this->shape);
	}
}

void Rects::checkCollision()
{
	sf::Vector2f bPos = this->ball->getPosition();
	sf::Vector2f pos = this->getPosition();
	if (bPos.x > pos.x
		and bPos.x < pos.x + this->width
		and bPos.y > pos.y
		and bPos.y < pos.y + this->length) {
		sf::Vector2f center = sf::Vector2f(pos.x + 2 / this->width, pos.y + 2 / this->length);

		if (bPos.x > pos.x + this->width - 10 and this->ball->xDir == 0 or this->ball->xDir == 2) {
			this->ball->xDir = 1;
		}
		else if (bPos.x < pos.x + 10 and this->ball->xDir == 1 or this->ball->xDir == 3) {
			this->ball->xDir = 0;
		}
		else {
			if (this->ball->yDir == 1) {
				this->ball->yDir = 0;
			}
			else {
				this->ball->yDir = 1;
			}
		}
		this->sound.setBuffer(this->buffer);
		this->sound.play();
		this->ball->addScore();
		this->isDead= true;

	}
}

sf::Vector2f Rects::getPosition()
{
	return this->shape.getPosition();
}

void Rects::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

const bool& Rects::getQuit() const
{
	return this->isDead;
}

