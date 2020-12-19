#include "PVPGameState.h"
PVPGameState::PVPGameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->Player2.mode = 2;
	this->Player2.setPosition(775.f, 0.f);
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->WinText.setFont(this->font);
	this->WinText.setString("");
	this->WinText.setPosition(250, 275);
	this->WinText.setCharacterSize(25);
}

PVPGameState::~PVPGameState()
{
}

void PVPGameState::endState()
{
	std::cout << "Ending gamestate" << "\n";
}


void PVPGameState::updateInputs(const float& dt)
{
	if (this->ball.lScore >= 5 or this->ball.rScore >= 5) {
		//this->isEnd = true;
		this->WinText.setString("Player win the game!\nPress Space Back to Menu");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->checkForQuit();
			this->ball.lScore = 0;
			this->ball.rScore = 0;
		}

	}
}

void PVPGameState::update(const float& dt)
{
	this->updateInputs(dt);
	if (!isEnd) {
		sf::Vector2f bPos = this->ball.getPosition();
		this->ball.update(dt, this->Player.getPosition(), this->Player2.getPosition(), this->Player.getWidth(), this->Player.getLength());
		this->Player.update(dt, bPos, this->ball.direction);
		this->Player2.update(dt, bPos, this->ball.direction);
	}
}

void PVPGameState::render(sf::RenderTarget* target)
{
	this->Player.render(target);
	this->Player2.render(target);
	this->ball.render(target);
	target->draw(WinText);
}