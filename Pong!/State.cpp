#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->isEnd = false;
	this->states = states;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->isEnd;
	// TODO: insert return statement here
}

void State::checkForQuit()
{
	this->isEnd = true;


}
