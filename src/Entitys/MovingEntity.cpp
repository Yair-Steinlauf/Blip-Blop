#include "MovingEntity.h"
#include "Movment/MovingState.h"
void MovingEntity::setDirection(sfPos direction)
{
	m_direction = direction;
}

void MovingEntity::update(float deltaTime)
{
	m_sprite.move(m_direction * deltaTime * m_speed);
}

void MovingEntity::movment(float deltaTime, const sf::Event& event)
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


