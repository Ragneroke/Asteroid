#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window,states)
{
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->PongText.setFont(this->font);
	this->PongText.setString("Asteroid");
	this->PongText.setPosition(170, 80);
	this->PongText.setCharacterSize(100);
	this->Option1.setFont(this->font);
	this->Option1.setString("Press 1 to Start");
	this->Option1.setCharacterSize(25);
	this->Option1.setPosition(265, 400);
	

}

MenuState::~MenuState()
{
}

void MenuState::endState()
{
}

void MenuState::updateInputs(const float& dt)
{
}

void MenuState::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		this->states->push(new GameState(this->window, this->states));
	}

}

void MenuState::render(sf::RenderTarget* target)
{
	target->draw(this->PongText);
	target->draw(this->Option1);
}
