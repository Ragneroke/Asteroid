#include "Game.h"

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    sf::VideoMode window_bounds(800, 600);
    std::string title = "None";
    unsigned frameRate_limit = 60;
    bool verticalSync_enabled = false;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> frameRate_limit;
        ifs >> verticalSync_enabled;
    }
	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(frameRate_limit);
    this->window->setVerticalSyncEnabled(verticalSync_enabled);
}

void Game::initStates()
{
    this->states.push(new MenuState(this->window, &this->states));
}

//Constructors, Destructors
Game::Game()
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    std::cout << "Ending Application" << "\n";
    delete this->window;
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();
    if (!this->states.empty()) {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->window->close();
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::render()
{
    this->window->clear();
    //Render items
    if (!this->states.empty()) {
        this->states.top()->render(this->window);
    }
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
