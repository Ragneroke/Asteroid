#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"
#include "GameState.h"
class MenuState :
    public State
{
public:
    MenuState(sf::RenderWindow* window, std::stack<State*>* states);
    ~MenuState();
	void endState();
	void updateInputs(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	//Variables
	bool isEnd = false;

protected:
	sf::Font font;
	sf::Text PongText;
	sf::Text Option1;

};


#endif
