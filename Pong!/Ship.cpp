
#include "Ship.h"

Ship::Ship(float x, float y)
{
	this->objectType = objectList::ship;
	this->width = 20.f;
	this->length = 20.f;
	if (!this->texture.loadFromFile("Resource/ship.png")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->texture.setSmooth(true);
	this->texture.setRepeated(true);
	this->circle.setTexture(&this->texture);
	this->isDead = false;
	this->circle.setRadius(20.f);
	this->circle.setPosition(x, y);
	this->circle.setOrigin(this->width, this->length);
	thrustAni.setRadius(20.f);
	thrustAni.setOrigin(sf::Vector2f(20.f, 20.f));
	thrustAni.setPosition(this->getPosition());
	this->fireCd = 0.5f;
	this->maxAcc = 10.f;
	this->speed = 0.f;
	this->velocity = sf::Vector2f(0.0001f, 0.0001f);
	this->angle = 0.f;
	this->rps = 100.f;
	this->Cd = 1.3f;

}

Ship::~Ship()
{
}

void Ship::update(const float& dt)
{
	turn(dt);
	slide(dt);
	trust(dt);
	drag(dt);
}

void Ship::render(sf::RenderTarget* target)
{
	target->draw(this->circle);
}

void Ship::checkCollision()
{
}

void Ship::setPosition(float x, float y)
{
}

const bool& Ship::getQuit() const
{
	// TODO: insert return statement here
	return this->isDead;
}


sf::Vector2f Ship::getForward()
{
	float angleInRad = -(90.0f - getCurAngle()) * 3.1415926f / 180.f;
	sf::Vector2f direction(cos(angleInRad), sin(angleInRad));
	return direction;
}

void Ship::turn(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		float curAngle = getCurAngle() - dt * rps;
		setRotation(curAngle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		float curAngle = getCurAngle() + dt * rps;
		setRotation(curAngle);
	}
}

void Ship::slide(const float& dt)
{
	sf::Vector2f dest = getPosition() + this->velocity * dt * 50.f;
	setLocation(dest);
}

void Ship::trust(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		isThrusting = true;
		curAcc = maxAcc;
		sf::Vector2f facingDir = getForward();
		sf::Vector2f vel = velocity + facingDir * curAcc * dt;
		if (sqrt(pow(vel.x, 2) + pow(vel.y, 2)) <= maxAcc) {
			velocity = velocity + facingDir * curAcc * dt;
		}
	}
	else {

		isThrusting = false;
	}
}

void Ship::drag(const float& dt)
{
	float mag = sqrt(pow(velocity.x, 2.f) + pow(velocity.y, 2.f));
	sf::Vector2f velDir = velocity / mag;
	float velMag = (float)sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	sf::Vector2f acc = velDir * Cd * velMag * (-1.0f);
	velocity = velocity + acc * dt;
}
