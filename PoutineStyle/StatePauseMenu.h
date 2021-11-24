#pragma once

#include "GameState.h"
#include "Button.h"

class StatePlayGame;

class StatePauseMenu : public GameState
{
	private:
		sf::View view;
		StatePlayGame* play;
		int w, h;

		Button playButton;
		Button quitButton;
		sf::Text pause;

	protected:
		void draw(double deltatime) override;
		void handleInput(double deltatime) override;

	public:
		StatePauseMenu(GameManager* game);
		~StatePauseMenu();

		void update(float deltaTime) override;
};

