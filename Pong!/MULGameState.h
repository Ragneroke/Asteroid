#ifndef MULGAMESTATE_H
#define MULGAMESTATE_H
#include "State.h"
class MULGameState :
    public State
{
public:
	MULGameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MULGameState();

	//Functions
	void endState();
	void updateInputs(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	//Variables
	bool isEnd = false;
	bool isPause = false;
private:
	Bar Player;
	Bar AI1;
	Bar AI2;
	Bar AI3;
	Bar AI4;
	Ball ball;
	sf::Font font;
	sf::Text WinText;
};


#endif