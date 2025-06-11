#include "GamePlay.h"

#include "Player.h"

static auto registerIt = Factory<BaseScreen>::instance().registerType(
	ObjectType::GamePlay,
	[](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen>
	{
		return std::make_unique<GamePlay>(window);
	}
);

GamePlay::GamePlay(sf::RenderWindow* window):
	BaseScreen(window), m_player(std::make_unique<Player>()),
	m_level(m_player.get()), 
	m_world(std::move(std::make_unique<b2World>(b2Vec2(0.f, 9.81f))))
{

}

void GamePlay::update(float deltaTime)
{
	m_level.update(deltaTime);
}

void GamePlay::draw()
{
	BaseScreen::draw();
	m_level.draw(*m_window);
}

void GamePlay::handleInput(const sf::Event& event, float deltaTime)
{
	//TODO:: maybe not needed parameters (const sf::Event& event, float deltaTime)
	m_player->movment();
}
