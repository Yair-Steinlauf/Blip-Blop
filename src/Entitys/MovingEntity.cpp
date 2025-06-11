#include "MovingEntity.h"
#include "Movment/MovingState.h"
MovingEntity::MovingEntity(sfPos pos, b2World* world):
	BaseEntity(pos, world),
	m_direction(0.f, 0.f),
	m_movement(nullptr),
	m_speed(100.f)
{
	m_bodyDef.type = b2_dynamicBody;
}
void MovingEntity::setDirection(sfPos direction)
{
	m_direction = direction;
}

void MovingEntity::update(float deltaTime)
{
	m_sprite.move(m_direction * deltaTime * m_speed);
}

void MovingEntity::movment()
{
	if (m_movement)
	{
		m_movement->enter(*this);
		auto newState = m_movement->move();
		if (newState)
		{
			m_movement = std::move(newState);
		}
	}
}


