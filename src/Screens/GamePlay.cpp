#include "GamePlay.h"

#include "Player.h"

static auto registerIt = Factory<BaseScreen, sf::RenderWindow*>::instance().registerType(
	ObjectType::GamePlay,
	[](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen>
	{
		return std::make_unique<GamePlay>(window);
	}
);

GamePlay::GamePlay(sf::RenderWindow* window):
	BaseScreen(window)
{
}

void GamePlay::update(float deltaTime)
{
}

void GamePlay::draw()
{
}

void GamePlay::handleInput(const sf::Event& event)
{
}
