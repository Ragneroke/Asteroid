#include "MULGameState.h"

MULGameState::MULGameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->AI1.mode = 1;
	this->AI1.setPosition(775.f, 0.f);
	this->AI1.topLimit = 120.f;
	this->AI2.mode = 1;
	this->AI2.setPosition(775.f, 300.f);
	this->AI2.botLimit = 300.f;
	this->AI3.mode = 1;
	this->AI3.setPosition(0.f, 0.f);
	this->AI3.topLimit = 120.f;
	this->Player.setPosition(0.f, 300.f);
	this->Player.botLimit = 300.f;
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->WinText.setFont(this->font);
	this->WinText.setString("");
	this->WinText.setPosition(250, 275);
	this->WinText.setCharacterSize(25);
}

MULGameState::~MULGameState()
{
}

void MULGameState::endState()
{
	std::cout << "Ending gamestate" << "\n";
}

void MULGameState::updateInputs(const float& dt)
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

void MULGameState::update(const float& dt)
{
	this->updateInputs(dt);
	if (!isPause) {
		sf::Vector2f bPos = this->ball.getPosition();
		this->ball.update(dt, this->Player.getPosition(), this->AI.getPosition(), this->Player.getWidth(), this->Player.getLength());
		this->Player.update(dt, bPos, this->ball.direction);
		this->AI1.update(dt, bPos, this->ball.direction);
		this->AI2.update(dt, bPos, this->ball.direction);
		this->AI3.update(dt, bPos, this->ball.direction);
	}
}

void MULGameState::render(sf::RenderTarget* target)
{
}
