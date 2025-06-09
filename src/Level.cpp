#include "Level.h"
#include "Factory.h"
#include "StandMovment.h"
#include "BaseEnemy.h"

Level::Level(Player* player)
	:m_player(player)
{
	m_entities.push_back(Factory<BaseEnemy>::instance().create(ObjectType::Dinosaur));
	
}

void Level::update(float deltaTime)
{

	m_player->update(deltaTime);
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
	m_player->draw(window);
}
