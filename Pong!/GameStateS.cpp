#include "GameStateS.h"
GameStateS::GameStateS(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	Player = Bar(&ball);
	power = Power(400.f, 0.f, &Player);
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->WinText.setFont(this->font);
	this->WinText.setString("");
	this->WinText.setPosition(250, 275);
	this->WinText.setCharacterSize(25);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
			Rects rect = Rects(j * 150.f, 100.f + 50.f * i, &this->ball);
			this->GameBoard.push_back(rect);
		}
	}
	for (int i = 0; i < 3; ++i) {
		Power power = Power(400.f, 0.f, &this->Player);
		this->powerups.push_back(power);
	}
	this->ball.setPosition(this->Player.getPosition().x + this->Player.getWidth() / 2, this->Player.getPosition().y);
	this->mousePos = sf::Mouse::getPosition(*window);
}

GameStateS::~GameStateS()
{
}

void GameStateS::endState()
{
	std::cout << "Ending GameStateS" << "\n";
}


void GameStateS::updateInputs(const float& dt)
{
	//Start the game
	if (!this->ball.isActive
		and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		or sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->ball.initialBall();
		this->ball.isActive = true;
		this->isStart = true;
	}

	//Check game Start
	if (!this->isStart) {
		this->ball.setPosition(this->Player.getPosition().x + this->Player.getWidth() / 2, this->Player.getPosition().y);
	}

	//Keep tracking ball condition
	this->isStart = this->ball.isActive;

	//Tracking mouse position in the window
	this->mousePos = sf::Mouse::getPosition(*window);
	if (this->ball.life <= 0) {
		this->isPause = true;
		this->WinText.setString("Game Over!\nPress Space Back to Menu");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->checkForQuit();
		}
	}
	else if (this->stageClear) {
		this->WinText.setString("Stage Clear!\nPress Space to Continue");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->checkForQuit();
		}
	}

}

void GameStateS::update(const float& dt)
{
	this->updateInputs(dt);
	if (!isPause) {
		this->bricksCount = 0;
		sf::Vector2f bPos = this->ball.getPosition();
		this->ball.update(dt);
		this->power.update(dt);
		this->Player.update(dt, this->mousePos);

		//Update bricks vector
		std::vector<Rects>::iterator it = this->GameBoard.begin();
		for (; it != this->GameBoard.end();) {
			if (!it->getQuit()) {
				++this->bricksCount;
			}
			it->update(dt);
			++it;
		}

		if (!this->powerups.empty()) {
			std::vector<Power>::iterator its = this->powerups.begin();
			for (; its != this->powerups.end();) {
				its->update(dt);
				++its;
			}
			--its;
			if (this->previousCount > this->bricksCount) {
				its->turnActive();
			}
			if (its->getPosition().y > 700 or its->getQuit()) {
				this->powerups.pop_back();
				std::cout << "pop!\n";
			}
		}
		this->previousCount = this->bricksCount;
		//Update powerups vector
		if (this->bricksCount == 0) {
			this->isPause = true;
			this->stageClear = true;
		}
	}
}

void GameStateS::render(sf::RenderTarget* target)
{
	this->Player.render(target);
	this->ball.render(target);
	this->power.render(target);
	for (auto rect : this->GameBoard) {
		rect.render(target);
	}
	for (auto power : this->powerups) {
		power.render(target);
	}
	target->draw(WinText);
}