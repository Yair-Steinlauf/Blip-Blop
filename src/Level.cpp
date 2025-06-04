#include "Level.h"

Level::Level(Player* player)
	:m_player(player)
{
	
}

void Level::update(float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	for (auto& entity : m_entities)
	{
		entity->draw(window);
	}
}
