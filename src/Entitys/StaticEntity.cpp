#include "StaticEntity.h"

StaticEntity::StaticEntity(sfPos pos, b2World* world)
	:BaseEntity(pos, world)
{
	m_bodyDef.type = b2_staticBody;

}
