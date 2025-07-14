#include "Controller.h"
#include "Screens/GamePlay.h"
#include "Screens/MenuScreen.h"
#include "Screens/HelpScreen.h"
#include "Factory/Factory.h"
#include "ScreensFactory.h"
#include "Constance.h"
#include "MusicManager.h"  // <-- הוסף את זה
#include <PauseScreen.h>

Controller::Controller() :
	m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window"))
	, m_screenStack()
{
	GameAnimations::initializeFrames();

	// התחל עם MenuScreen ותעביר את ה-Controller
	auto menuScreen = std::make_unique<MenuScreen>(m_window.get(), this);
	m_screenStack.push(std::move(menuScreen));

	// הפעל מוזיקת רקע (אם היא לא מופעלת כבר)
	MusicManager::getInstance().startBackgroundMusic();
}

void Controller::run()
{
	sf::Clock clock;
	while (m_window->isOpen())
	{
		sf::Event event;
		float deltaTime = clock.restart().asSeconds();
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				// עצור מוזיקה לפני סגירה
				MusicManager::getInstance().stopBackgroundMusic();
				m_window->close();
			}
		}

		if (!m_screenStack.empty()) {
			m_screenStack.top()->handleInput(event, deltaTime);
			m_screenStack.top()->update(deltaTime);
			m_window->clear();
			m_screenStack.top()->draw();
			m_window->display();
		}
	}
}

//void Controller::switchToGamePlay() {
//	// מחק את המסך הנוכחי
//	if (!m_screenStack.empty()) {
//		m_screenStack.pop();
//	}
//
//	// הוסף את מסך המשחק
//	auto gamePlayScreen = std::make_unique<GamePlay>(m_window.get());
//	m_screenStack.push(std::move(gamePlayScreen));
//}

void Controller::switchToGamePlay() {
	while (!m_screenStack.empty()) {
		m_screenStack.pop(); 		
	}
	auto gamePlay = std::make_unique<GamePlay>(m_window.get());
	gamePlay->setController(this); // הוספת החיבור

	m_screenStack.push(std::move(gamePlay));
}

void Controller::switchToHelp() {
		// הוסף את מסך העזרה
	auto helpScreen = std::make_unique<HelpScreen>(m_window.get(), this);
	m_screenStack.push(std::move(helpScreen));
}

void Controller::backCommand() {
	// מחק את המסך הנוכחי (HelpScreen או GamePlay)
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}	
}

void Controller::pauseGame() {
	// בדיקה שאנחנו נמצאים במסך משחק
	GamePlay* currentGamePlay = getCurrentGamePlay();
	if (currentGamePlay) {
		auto pauseScreen = std::make_unique<PauseScreen>(m_window.get(), this, currentGamePlay);
		m_screenStack.push(std::move(pauseScreen));
	}
}

void Controller::resumeFromPause() {
	// הסרת מסך ה-pause ע"י pop מה-stack
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}
}

void Controller::switchToGameOver(GameOverScreen::GameResult result, int score)
{
	// Clear the current screen stack and push the game over screen
	/*while (!m_screenStack.empty()) {
		m_screenStack.pop();
	}*/

	auto gameOverScreen = std::make_unique<GameOverScreen>(m_window.get(), result, score, this);
	m_screenStack.push(std::move(gameOverScreen));
}

GamePlay* Controller::getCurrentGamePlay()
{
	// בדיקה שהמסך הנוכחי הוא GamePlay
	if (!m_screenStack.empty()) {
		return dynamic_cast<GamePlay*>(m_screenStack.top().get());
	}
	return nullptr;

}



