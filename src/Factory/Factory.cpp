#include "Factory.h"
#include "BaseEntity.h"

Factory& Factory::instance()
{
	static auto instance = Factory();
	return instance;
}

bool Factory::registerType(ObjectType t, FuncType f)
{
	m_map.emplace(t, f);
	return true;
}

std::unique_ptr<BaseEntity> Factory::create(ObjectType t, sfPos pos, b2World* world) const
{
	auto object = m_map.find(t);
	if (object == m_map.end())
		throw std::runtime_error("Cannot Find Current Object\n");
	return (object->second)(pos, world);
}
