#ifndef BHGAMESTATE_H
#define BHGAMESTATE_H
#include "State.h"
class BHGameState :
    public State
{
public:
	BHGameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~BHGameState();

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
	Bar AI;
	Ball ball;
	sf::Font font;
	sf::Text WinText;
};

#endif