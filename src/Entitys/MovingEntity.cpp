#include "MovingEntity.h"

void MovingEntity::update(float deltaTime)
{
	m_sprite.setPosition(m_nextPosition);
}
