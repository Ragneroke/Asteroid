#include "Bar.h"

Bar::Bar(Ball* ball) {
	this->width = 120.f;
	this->length = 10.f;
	this->shape.setSize(sf::Vector2f(this->width, this->length));
	this->shape.setPosition(400.f - (this->width) / 2, 600.f - this->length);
	this->movementSpeed = 400.f;
	this->idleColor = sf::Color::White;
	this->activeColor = sf::Color::Red;
	this->mode = 0;
	this->lLimit = 0.f;
	this->rLimit = 680.f;
	this->ball = ball;
	this->score = 0;

	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->text.setFont(this->font);
	this->text.setString("Score: 0");
	this->text.setPosition(600, 5);
	this->text.setCharacterSize(25);


	if (!this->buffer.loadFromFile("Resource/Pop.ogg")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->sound.setBuffer(this->buffer);
}

Bar::~Bar() {

}


void Bar::move(const float& dt, const float y) {
	this->shape.move(y * this->movementSpeed * dt, 0);

}

void Bar::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Bar::playerMoving(const float& dt, sf::Vector2i mPos)
{
	this->shape.setFillColor(this->idleColor);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (this->shape.getPosition().x > this->lLimit) {
			this->move(dt, -1.f);
			this->shape.setFillColor(this->activeColor);
		}

	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (this->shape.getPosition().x < this->rLimit) {
			this->move(dt, 1.f);
			this->shape.setFillColor(this->activeColor);
		}
	}
	else if(mPos.x > 0 and mPos.x < 800 - this->width){
		this->shape.setPosition((float)mPos.x, 600.f - this->length);
	}
}



bool Bar::intersects(const sf::CircleShape& c, const sf::RectangleShape& r)
{
	sf::FloatRect fr = r.getGlobalBounds();
	sf::Vector2f topLeft(fr.left, fr.top);
	sf::Vector2f topRight(fr.left + fr.width, fr.top);
	sf::Vector2f botLeft(fr.left, fr.top + fr.height);
	sf::Vector2f botRight(fr.left + fr.width, fr.top + fr.height);

	return contains(c, topLeft) ||
		contains(c, topRight) ||
		contains(c, botLeft) ||
		contains(c, botRight);
}

bool Bar::contains(const sf::CircleShape& c, const sf::Vector2f& p)
{
	sf::Vector2f center = c.getPosition();
	float a = (p.x - center.x);
	float b = (p.y - center.y);
	a *= a;
	b *= b;
	float r = c.getRadius() * c.getRadius();
	return ((a + b) < r);
}

void Bar::checkCollision()
{
	sf::Vector2f bPos = this->ball->getPosition();
	sf::Vector2f pos = this->getPosition();
	if (bPos.x > pos.x
		and bPos.x < pos.x + this->width
		and bPos.y > pos.y
		and bPos.y < pos.y + this->length
		) {
		if (bPos.x < pos.x + 30.f) {
			if (this->ball->xDir == 0) {
				this->ball->xDir = 2;
			}
			else if (this->ball->xDir == 1) {
				this->ball->xDir = 3;
			}
		}
		if (bPos.x > pos.x + 90.f) {
			if (this->ball->xDir == 0) {
				this->ball->xDir = 2;
			}
			else if (this->ball->xDir == 1) {
				this->ball->xDir = 3;
			}
		}
		this->ball->yDir = 1;
		this->sound.setBuffer(this->buffer);
		this->sound.play();
	}

}

void Bar::getWider()
{
	this->width += 60;
	this->shape.setSize(sf::Vector2f(this->width, this->length));

}

void Bar::addScore()
{
	this->score += 50;
	this->text.setString("Score: " + std::to_string(this->score));
}

sf::Vector2f Bar::getPosition()
{
	return this->shape.getPosition();

}

float Bar::getWidth()
{
	return this->width;
}

float Bar::getLength()
{
	return this->length;
}

void Bar::update(const float& dt, sf::Vector2i mPos) {
	if (mode == 0)
		playerMoving(dt, mPos);
	this -> checkCollision();
}


void Bar::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}

