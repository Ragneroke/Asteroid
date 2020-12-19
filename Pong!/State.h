#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <map>
#include <cmath>
#include "Bar.h"
#include "Ball.h"
#include "Rects.h"
#include "Power.h"
#include "GameObject.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"




class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool isEnd;
public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void updateInputs(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};


#endif
