#pragma once

#include <SFML/Graphics.hpp>
#include "Screens/BaseScreen.h"
#include <memory>
#include <stack>
using ScreenPtrStack = std::stack<std::unique_ptr<BaseScreen>>;

class Controller {
public:
	Controller();
	void run();
	~Controller() = default;
private:
	ScreenPtrStack m_screenStack;
	std::unique_ptr<sf::RenderWindow> m_window;
};