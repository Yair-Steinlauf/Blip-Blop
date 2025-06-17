#include "Level.h"
#include "Factory.h"
#include "BaseEnemy.h"
#include "Constance.h"
Level::Level(Player* player , b2World* world)
	:m_player(player), m_world(world)
{
	//m_entities.push_back(Factory<BaseEntity>::instance().create(ObjectType::SMURF, {5,5}, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::FLOOR, sfPos{500,550/*0,SCREEN_HEIGHT - 20 */}, m_world));

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
