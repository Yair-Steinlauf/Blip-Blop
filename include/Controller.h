#pragma once

#include "BaseScreen.h"
#include <memory>
#include <stack>

class GamePlay;
using ScreenPtrStack = std::stack<std::unique_ptr<BaseScreen>>;

class Controller {
public:
	Controller();
	void run();
	void switchToGamePlay();
	void switchToHelp();      
	void backCommand();      
	void pauseGame();
	void resumeFromPause();
	~Controller() = default;

private:
	ScreenPtrStack m_screenStack;
	std::unique_ptr<sf::RenderWindow> m_window;
	GamePlay* getCurrentGamePlay();
};