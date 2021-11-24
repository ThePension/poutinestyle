#pragma once

#include "GameState.h"
#include "Button.h"

class StatePauseMenu : public GameState
{
	private:
		sf::View view;
		Button playButton;
		Button quitButton;
		Button settingsButton;

	protected:
		void draw(double deltatime) override;
		void handleInput(double deltatime) override;

	public:
		StatePauseMenu();
		~StatePauseMenu();
		void update(float deltaTime) override;
};

