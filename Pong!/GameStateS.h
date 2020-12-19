#ifndef GAMESTATES_H
#define GAMESTATES_H
#include "State.h"
#include "MenuState.h"
class GameStateS :
    public State
{
public:
	GameStateS(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameStateS();

	//Functions
	void endState();
	void updateInputs(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	std::vector<Rects> GameBoard;
	std::vector<Power> powerups;

	//Variables
	bool isEnd = false;
	bool isPause = false;
private:
	Bar AI;
	Ball ball;
	Bar Player;
	Power power;
	sf::Font font;
	sf::Text WinText;
	sf::Vector2i mousePos;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int powNums = 5;
	int bricksCount = 20;
	int previousCount = 20;
	bool isStart = false;
	bool stageClear = false;
};

#endif