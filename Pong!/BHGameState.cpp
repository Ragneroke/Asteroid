#include "BHGameState.h"

BHGameState::BHGameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->AI.mode = 1;
	this->AI.setPosition(775.f, 0.f);
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->ball.isBhMode = true;
	this->WinText.setFont(this->font);
	this->WinText.setString("");
	this->WinText.setPosition(250, 275);
	this->WinText.setCharacterSize(25);
}

BHGameState::~BHGameState()
{
}

void BHGameState::endState()
{
}

void BHGameState::updateInputs(const float& dt)
{
	if (this->ball.lScore >= 5) {
		this->WinText.setString("Player left win the game!\nPress Space Back to Menu");
		this->isPause = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->checkForQuit();
			this->ball.lScore = 0;
			this->ball.rScore = 0;
		}

	}
	else if (this->ball.rScore >= 5) {
		this->WinText.setString("Player right win the game!\nPress Space Back to Menu");
		this->isPause = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->checkForQuit();
			this->ball.lScore = 0;
			this->ball.rScore = 0;
		}
	}
}

void BHGameState::update(const float& dt)
{
	this->updateInputs(dt);
	if (!isPause) {
		sf::Vector2f bPos = this->ball.getPosition();
		this->ball.update(dt, this->Player.getPosition(), this->AI.getPosition(), this->Player.getWidth(), this->Player.getLength());
		this->Player.update(dt, bPos, this->ball.direction);
		this->AI.update(dt, bPos, this->ball.direction);
	}
}

void BHGameState::render(sf::RenderTarget* target)
{
	this->Player.render(target);
	this->AI.render(target);
	this->ball.render(target);
	target->draw(WinText);
}
