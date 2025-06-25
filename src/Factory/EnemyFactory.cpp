#include "EnemyFactory.h"
#include "BaseEntity.h"

EnemyFactory& EnemyFactory::instance()
{
	static auto instance = EnemyFactory();
	return instance;
}

bool EnemyFactory::registerType(ObjectType t, FuncType f)
{
	m_map.emplace(t, f);
	return true;
}

std::unique_ptr<BaseEntity> EnemyFactory::create(ObjectType t, sfPos pos, b2World* world, Player* player) const
{
	auto object = m_map.find(t);
	if (object == m_map.end())
		throw std::runtime_error("Cannot Find Current Object\n");
	return (object->second)(pos, world, player);
}
	