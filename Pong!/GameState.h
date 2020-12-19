#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "MenuState.h"
class GameState : public State
{
public:
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void endState();
	void updateInputs(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void launchBullet(const float& dt);
	void spawnAsteroid();
	bool checkCollision(GameObject object1, GameObject object2);
	int getBucketIndex(sf::Vector2f location);
	bool isContain(std::vector<int> vectorList, int possibleIndex);
	std::vector<int> getBucketIndexList(GameObject object);
	void putAllInBucket();
	void garbageCollecter();
	void destroyBullet(Bullet* object);
	void updateIndex();
	void checkObjectsCollision();
	int processCollision(GameObject* object1, GameObject* object2);
	void addGameObjects();
	int asteroidSearch(Asteroid* object);
	std::vector<std::vector<GameObject*>> bucket;
	std::vector<Rects> GameBoard;
	std::vector<Power> powerups;
	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;
	std::vector<GameObject*> gameObjects;

	//Variables
	bool isEnd = false;
	bool isPause = false;
private:
	Ship* player;
	sf::Font font;
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text overText;
	bool gameOver = false;
	int health = 3;
	int score = 0;
	sf::Vector2i mousePos;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Clock clock;
	int powNums = 5;
	int bricksCount = 24;
	int previousCount = 24;
	//For bullet cooldown
	float lastFire = 0.f;
	float fireCd = 0.5f;

	//For Asteroid cooldown
	float lastSpawn = 0.f;
	float spawnCd = 5.f;

	//For Ship invisi
	float invisi = false;
	float lastHit = 0.f;
	float hitCd = 1.f;
	//For bucket numbers
	int xBuckets = 4;
	int yBuckets = 4;
	int xInterval = 800 / xBuckets;
	int yInterval = 600 / yBuckets;
	bool isStart = false;
	bool stageClear = false;

	//Buffer
	sf::SoundBuffer pewBuffer;
	sf::Sound pewSound;

	sf::SoundBuffer exBuffer;
	sf::Sound expSound;
};

#endif