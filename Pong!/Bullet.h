#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
class Bullet :
    public GameObject
{
private:
    sf::Vector2f dir;
    float speed;
    void slide(const float& dt);

public:
    Bullet(sf::Vector2f pos, sf::Vector2f faceDir, float speed);
    ~Bullet();
    virtual void update(const float& dt) override;
    void render(sf::RenderTarget* target);
};



#endif