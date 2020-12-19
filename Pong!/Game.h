#ifndef GAME_H
#define GAME_H
#include "GameState.h"
#include "MenuState.h"
#include "GameStateS.h"
class Game
{
protected:
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	//Initialization
	void initWindow();
	void initStates();
public:
	Game();
	virtual ~Game();

	//Functions
	void updateSFMLEvents();
	void update();
	void updateDt();
	void render();
	void run();

};

#endif