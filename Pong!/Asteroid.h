#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include <iostream>
#include <cmath>
class Asteroid :
    public GameObject
{
public:
    int asIndex = 2;
    Asteroid(int index, float baseSpeed);
    Asteroid(int index, sf::Vector2f location, float baseSpeed);
    void randomPos();
    virtual void update(const float& dt) override;
    void render(sf::RenderTarget* target);
    void slide(const float& dt);
    void bounce(sf::Vector2f newDir);
    void setIndex(int index);
private:
    sf::Vector2f dir;
    float speed;
    sf::Texture texture;
    float radiusArray[3] = { 10.f,20.f,40.f };

};


#endif
