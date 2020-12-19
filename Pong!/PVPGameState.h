#ifndef PVPGAMESTATE_H
#define PVPGAMESTATE_H
#include "State.h"
class PVPGameState :
    public State
{
public:
	PVPGameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~PVPGameState();

	//Functions
	void endState();
	void updateInputs(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	//Variables
	bool isEnd = false;
private:
	Bar Player;
	Bar Player2;
	Ball ball;
	sf::Font font;
	sf::Text WinText;
};

#endif