#include "Ball.h"

Ball::Ball()
{
	this->radius = 5.f;
	this->shape.setRadius(5.f);
	this->shape.setPosition(400, 300);
	this->movementSpeed = 5.f;
	this->currentSpeed = movementSpeed;
	this->idleColor = sf::Color::White;
	this->dx = 0.f;
	this->dy = 0.f;
	this->ody = 0.f;
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->lifeText.setFont(this->font);
	this->lifeText.setString("LIFE: 3");
	this->lifeText.setPosition(5, 5);
	this->lifeText.setCharacterSize(25);
	this->scoreText.setFont(this->font);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(600, 5);
	this->scoreText.setCharacterSize(25);
	if (!this->buffer.loadFromFile("Resource/Dead.wav")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->sound.setBuffer(this->buffer);
}

Ball::~Ball()
{
}

void Ball::update(const float& dt)
{
	if (this->isActive) {
		sf::Vector2f bPos = this->shape.getPosition();
		this->checkCollision();
		this->checkMovement();
		this->shape.move(this->dx, this->dy);
	}
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->lifeText);
	target->draw(this->scoreText);
}

void Ball::initialBall()
{  
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and !this->isActive) {
		this->dx = this->movementSpeed;
		this->dy = -this->movementSpeed;
		this->isActive = true;
	}
}



void Ball::resetPosition() {
	this->shape.setPosition(400, 300);
}

void Ball::checkCollision()
{
	sf::Vector2f bPos = this->shape.getPosition();
	if (bPos.x <= this->radius) {
		this->xDir = 1;
		if (!this->buffer.loadFromFile("Resource/Wall.wav")) {
			std::cout << "Error loading file\n";
			system("pause");
		}
		this->sound.setBuffer(this->buffer);
		this->sound.play();
	}
	else if (bPos.x >= 800 - this->radius) {
		this->xDir = 0;
		if (!this->buffer.loadFromFile("Resource/Wall.wav")) {
			std::cout << "Error loading file\n";
			system("pause");
		}
		this->sound.setBuffer(this->buffer);
		this->sound.play();
	}
	if (bPos.y <= this->radius) {
		this->yDir = 0;
		if (!this->buffer.loadFromFile("Resource/Wall.wav")) {
			std::cout << "Error loading file\n";
			system("pause");
		}
		this->sound.setBuffer(this->buffer);
		this->sound.play();
	}
	if (bPos.y >= 600) {
		this->life -= 1;
		this->lifeText.setString("LIFE: " + std::to_string(this->life));
		if (!this->buffer.loadFromFile("Resource/Dead.wav")) {
			std::cout << "Error loading file\n";
			system("pause");
		}
		this->sound.setBuffer(this->buffer);
		this->sound.play();
		this->isActive = false;
	}
}

void Ball::checkMovement()
{
	if (xDir == 1) {
		this->dx = this->currentSpeed;
	}
	else if (xDir == 0) {
		this->dx = -this->currentSpeed;
	}
	else if (xDir == 2) {
		this->dx = -2 * this->currentSpeed;
	}
	else if (xDir == 3) {
		this->dx = 2 * this->currentSpeed;
	}
	if (yDir == 1) {
		this->dy = -this->currentSpeed;
	}
	else if (yDir == 0) {
		this->dy = this->currentSpeed;
	}
}

void Ball::setPosition(float x, float y)
{
	this->shape.setPosition(x,y);
}

void Ball::addScore()
{
	this->score += 50;
	this->scoreText.setString("Score: " + std::to_string(this->score));
}


sf::Vector2f Ball::getPosition() {
	return this->shape.getPosition();
}

sf::CircleShape Ball::getShape()
{
	return this->shape;
}


