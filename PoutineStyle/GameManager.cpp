#include "GameManager.h"

// Needed here to avoid circular dependency
#include "GameState.h"
#include "StatePlayGame.h"
#include "StateMainMenu.h"
#include "StatePauseMenu.h"
#include "StateGameOverMenu.h"

GameManager::GameManager()
{
    window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "RayCasting with SFML", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    // window->setFramerateLimit(144);
    sf::View view(sf::FloatRect(0, 0, float(this->windowWidth), float(this->windowWidth)));
    window->setView(view);
    StateMainMenu* stateMainMenu = new StateMainMenu(this);
    states.push(stateMainMenu);


    window->setPosition(sf::Vector2i(500, 0));

    font = sf::Font();
    font.loadFromFile("CollegiateBlackFLF.ttf");

    // Music
    gameMusic = new sf::Music();
    menuMusic = new sf::Music();
    menuMusic->openFromFile("../PoutineStyle/Music/MainMenuMusic.wav");
    menuMusic->play();

}

GameManager::~GameManager()
{
    gameMusic->stop(); menuMusic->stop();
    delete gameMusic; delete menuMusic;
}

void GameManager::gameLoop()
{
    sf::Text fpsText("", font, 15);
    fpsText.setFillColor(sf::Color::Red);
    float dt_counter = 0.0f; // delta time for multiple frames, for calculating FPS smoothly
    int frame_counter = 0; // counts frames for FPS calculation
    int64_t frame_time_micro = 0; // time needed to draw frames in microseconds
    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // Update FPS, smoothed over time
        if (dt_counter >= 0.1) {
            int fps = int(frame_counter / dt_counter);
            frame_time_micro /= frame_counter;
            fpsText.setString(std::to_string(fps) +" fps");
            dt_counter = 0.0f;
            frame_counter = 0;
            frame_time_micro = 0;
        }
        dt_counter += deltaTime;
        ++frame_counter;
        
        // Clear the window
        window->clear();

        if (peekState() != nullptr)
        {
            peekState()->update(deltaTime);
        }

        // Draw fps counter
        if (drawFPS)
        {
            window->draw(fpsText);
        }

        // Add elapsed time
        frame_time_micro += clock.getElapsedTime().asMicroseconds();
        window->display();
    }
}

void GameManager::pushState(GameState* state) {
    this->states.push(state);
}

void GameManager::popState() {
    if (!this->states.empty()) {
        GameState * stateToDelete = this->states.top();
        delete stateToDelete;
        stateToDelete = nullptr;
        this->states.pop();
    }
}

void GameManager::changeState(GameState* state) {
    if (!this->states.empty()) {
        popState();
    }
    pushState(state);
}

GameState* GameManager::peekState(int n)
{
    int size = this->states.size();

    std::list<GameState*> backup;
    GameState* state;

    if (size < n)
    {
        return nullptr;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            backup.push_back(this->states.top());
            this->states.pop();
        }

        state = this->states.top();

        for (int i = 0; i < n; i++)
        {
            this->states.push(backup.back());
            backup.pop_back();
        }
    }

    return state;
}

