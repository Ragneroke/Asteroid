#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window,states)
{
	this->player = new Ship(398.f, 300.f);
	this->player->index = 0;
	this->gameObjects.push_back(this->player);
	//Initial score text
	if (!font.loadFromFile("Resource/Goldman-Regular.ttf")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->scoreText.setFont(this->font);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(600, 5);
	this->scoreText.setCharacterSize(25);
	this->healthText.setFont(this->font);
	this->healthText.setString("Health: 3");
	this->healthText.setPosition(50, 5);
	this->healthText.setCharacterSize(25);
	this->overText.setFont(this->font);
	this->overText.setString("    GameOver!\n Press Enter to Continue");
	this->overText.setPosition(300, 100);
	this->overText.setCharacterSize(30);

	if (!this->pewBuffer.loadFromFile("Resource/laserpew.ogg")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->pewSound.setBuffer(this->pewBuffer);

	if (!this->exBuffer.loadFromFile("Resource/explosion.wav")) {
		std::cout << "Error loading file\n";
		system("pause");
	}
	this->expSound.setBuffer(this->exBuffer);
	bucket.clear();
	for (unsigned int i = 0; i < 16; ++i) {
		bucket.push_back(std::vector<GameObject*>());
	}

}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending gamestate" << "\n";
}


void GameState::updateInputs(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		launchBullet(dt);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) and gameOver) {
		this->states->pop();
	}

}

void GameState::update(const float& dt)
{
	garbageCollecter();
	updateIndex();
	putAllInBucket();
	this->updateInputs(dt);
	spawnAsteroid();
	checkObjectsCollision();
	addGameObjects();
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->update(dt);
	}
}

void GameState::render(sf::RenderTarget* target)
{

	for (auto& object : this->gameObjects) {
		object->render(target);
	}
	target->draw(scoreText);
	target->draw(healthText);
	if (gameOver) {
		target->draw(overText);
	}
	
}

void GameState::launchBullet(const float& dt)
{
	sf::Time time = this->clock.getElapsedTime();
	if (this->lastFire + this->fireCd < time.asSeconds()) {
		Bullet bullet(player->getPosition(), player->getForward(), 500.f);
		bullets.push_back(bullet);
		this->pewSound.play();
		this->lastFire = time.asSeconds();
	}
}

void GameState::spawnAsteroid()
{
	sf::Time time = this->clock.getElapsedTime();
	if (this->lastSpawn + this->spawnCd < time.asSeconds() and asteroids.size() <= 10) {
		Asteroid asteroid(2, 50.f);
		asteroids.push_back(asteroid);
		this->lastSpawn = time.asSeconds();
	}
}

bool GameState::checkCollision(GameObject object1, GameObject object2)
{
	if (object1.index != object2.index) {
		sf::Vector2f distanceVector = object1.getPosition() - object2.getPosition();
		float distance = (float)(sqrt(pow(distanceVector.x, 2) + pow(distanceVector.y, 2)));
		float radiusSum = object1.getRadius() + object2.getRadius();
		if (radiusSum >= distance) {
			return true;
		}
	}
	return false;
}

int GameState::getBucketIndex(sf::Vector2f location)
{
	int xIndex = (int)floor(location.x / xInterval);
	if (xIndex < 0) {
		xIndex = 0;
	}
	else if (xIndex >= xBuckets) {
		xIndex = xBuckets - 1;
	}
	int yIndex = (int)floor(location.y / yInterval);
	if (yIndex < 0) {
		yIndex = 0;
	}
	else if (yIndex >= xBuckets) {
		yIndex = yBuckets - 1;
	}
	int buckIndex = xIndex + 4 * yIndex;
	if (buckIndex >= 16) {
		std::cout << ">=16";
	}
	return buckIndex;
}

bool GameState::isContain(std::vector<int> vectorList, int possibleIndex)
{
	for (unsigned int i = 0; i < vectorList.size(); i++) {
		if (vectorList[i] == possibleIndex) {
			return true;
		}
	}
	return false;
}

std::vector<int> GameState::getBucketIndexList(GameObject object)
{
	std::vector<int> indexList;

	sf::Vector2f corner;
	float radius = object.getRadius();
	int bucketIndex;
	//left upper
	corner = object.getPosition() + sf::Vector2f(-radius, -radius);
	bucketIndex = getBucketIndex(corner);
	if (!this->isContain(indexList, bucketIndex)) {
		indexList.push_back(bucketIndex);
	}

	//left down
	corner = object.getPosition() + sf::Vector2f(-radius, +radius);
	bucketIndex = getBucketIndex(corner);
	if (!this->isContain(indexList, bucketIndex)) {
		indexList.push_back(bucketIndex);
	}
	//right upper
	corner = object.getPosition() + sf::Vector2f(+radius, -radius);
	bucketIndex = getBucketIndex(corner);
	if (!this->isContain(indexList, bucketIndex)) {
		indexList.push_back(bucketIndex);
	}
	//right down
	corner = object.getPosition() + sf::Vector2f(+radius, +radius);
	bucketIndex = getBucketIndex(corner);
	if (!this->isContain(indexList, bucketIndex)) {
		indexList.push_back(bucketIndex);
	}
	return indexList;
}

void GameState::putAllInBucket()
{
	for (unsigned int i = 0; i < bucket.size(); ++i) {
		bucket[i].clear();
	}

	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		std::vector<int> bucketIndexList = getBucketIndexList(*gameObjects[i]);
		for (unsigned int j = 0; j < bucketIndexList.size(); ++j) {
			bucket[bucketIndexList[j]].push_back(gameObjects[i]);
		}

	}
}

void GameState::garbageCollecter()
{
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		if (gameObjects[i]->objectType == GameObject::objectList::bullet) {
			if (gameObjects[i]->getPosition().x < 0.f
				or gameObjects[i]->getPosition().x > 800.f
				or gameObjects[i]->getPosition().y < 0.f
				or gameObjects[i]->getPosition().y > 600.f) {
				int index = gameObjects[i]->index;
				for (unsigned j = 0; j < bullets.size(); ++j) {
					if (bullets[j].index == index) {
						bullets.erase(bullets.begin() + j);
					}
				}
				return;
			}
		}
	}
}

void GameState::destroyBullet(Bullet* object)
{
	for (unsigned int i = 0; i < bullets.size(); ++i) {
		if (object == &bullets[i]) {
			bullets.erase(bullets.begin() + i);
			return;
		}
	}
}

void GameState::updateIndex()
{
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->index = i;
	}
}

void GameState::checkObjectsCollision()
{
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		std::vector<int> bucketIndexList = getBucketIndexList(*gameObjects[i]);
		for (unsigned int j = 0; j < bucketIndexList.size(); ++j) {
			for (unsigned int k = 0; k < bucket[bucketIndexList[j]].size(); ++k) {
				bool collided = checkCollision(*gameObjects[i], *bucket[bucketIndexList[j]][k]);
				if (collided) {
					int result = processCollision(gameObjects[i], bucket[bucketIndexList[j]][k]);
					if (result == -1) {
						return;
					}
				}


			}
			bucket[bucketIndexList[j]].push_back(gameObjects[i]);
		}
	}
}

int GameState::processCollision(GameObject* object1, GameObject* object2)
{
	if (object1->objectType == GameObject::objectList::asteroid and
		object2->objectType == GameObject::objectList::asteroid) {
		Asteroid* asteroid1 = dynamic_cast<Asteroid*>(object1);
		Asteroid* asteroid2 = dynamic_cast<Asteroid*>(object2);
		sf::Vector2f difference = asteroid1->getPosition() - asteroid2->getPosition();
		sf::Vector2f unitDiff1 = difference / (sqrt(pow(difference.x, 2.f) + pow(difference.y, 2.f)));
		sf::Vector2f unitDiff2 = sf::Vector2f(unitDiff1.x * (-1.f), unitDiff1.y * (-1.f));
		asteroid1->bounce(unitDiff1);
		asteroid2->bounce(unitDiff2);
	}

	if ((object1->objectType == GameObject::objectList::bullet and
		object2->objectType == GameObject::objectList::asteroid)
		or (object1->objectType == GameObject::objectList::asteroid
			and object2->objectType == GameObject::objectList::bullet)) {
		this->score += 10;
		scoreText.setString("Score: " + std::to_string(score));
		Asteroid* asteroid;
		Bullet* bullet;
		if (object2->objectType == GameObject::objectList::asteroid) {
			asteroid = dynamic_cast<Asteroid*>(object2);
			bullet = dynamic_cast<Bullet*>(object1);
		}
		else {
			asteroid = dynamic_cast<Asteroid*>(object1);
			bullet = dynamic_cast<Bullet*>(object2);
		}

		if (asteroid->asIndex == 0) {
			destroyBullet(bullet);
			int asteroidIndex = asteroidSearch(asteroid);
			if (asteroidIndex != -1) {
				asteroids.erase(asteroids.begin() + asteroidIndex);
			}
			this->expSound.play();
			return -1;
		}
		else if (asteroid->asIndex == 1) {
			destroyBullet(bullet);
			sf::Vector2f spawnLocation = asteroid->getPosition();
			int asteroidIndex = asteroidSearch(asteroid);
			if (asteroidIndex != -1) {
				asteroids.erase(asteroids.begin() + asteroidIndex);
			}
			asteroids.push_back(Asteroid(0, spawnLocation, 20.f));
			asteroids.push_back(Asteroid(0, spawnLocation, 20.f));
			this->expSound.play();
		}else if (asteroid->asIndex == 2) {
			destroyBullet(bullet);
			sf::Vector2f spawnLocation = asteroid->getPosition();
			int asteroidIndex = asteroidSearch(asteroid);
			if (asteroidIndex != -1) {
				asteroids.erase(asteroids.begin() + asteroidIndex);
			}
			asteroids.push_back(Asteroid(1, spawnLocation, 20.f));
			asteroids.push_back(Asteroid(1, spawnLocation, 20.f));
			this->expSound.play();
		}
	}
	if ((object1->objectType == GameObject::objectList::ship and
		object2->objectType == GameObject::objectList::asteroid)
		or (object1->objectType == GameObject::objectList::asteroid
			and object2->objectType == GameObject::objectList::ship)) {
		sf::Time time = this->clock.getElapsedTime();
		if (lastHit + hitCd < time.asSeconds()) {
			this->health--;
			this->expSound.play();
			healthText.setString("Health: " + std::to_string(this->health));
			lastHit = time.asSeconds();
			if (health <= 0) {
				gameOver = true;
				delete this->player;
				this->player = nullptr;
			}
		}

	}
	return 0;
}

void GameState::addGameObjects()
{
	gameObjects.clear();
	if (this->player != nullptr) {
		gameObjects.push_back(this->player);
	}
	for (unsigned int i = 0; i < asteroids.size(); ++i) {
		gameObjects.push_back(&asteroids[i]);
	}

	for (unsigned int i = 0; i <bullets.size(); ++i) {
		gameObjects.push_back(&bullets[i]);
	}

}

int GameState::asteroidSearch(Asteroid* object)
{
	for (unsigned int i = 0; i < asteroids.size(); ++i) {
		if (object == &asteroids[i]) {
			return i;
		}
	}
	return -1;
}
