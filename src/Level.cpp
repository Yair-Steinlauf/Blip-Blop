#include "Level.h"
#include "Factory.h"
#include "BaseEnemy.h"

Level::Level(Player* player)
	:m_player(player)
{

	m_entities.push_back(Factory<BaseEntity>::instance().create(ObjectType::SMURF));
	
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
