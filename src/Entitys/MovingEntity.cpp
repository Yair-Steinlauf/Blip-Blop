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
	sync(); 
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

void MovingEntity::initBox2d(sfPos pos)
{
	BaseEntity::initBox2d(pos);
	b2FixtureDef fix;
	fix.shape = &m_polygonShape;
	fix.density = 1.0f;
	fix.friction = 0.3f;
	fix.restitution = 0.0f;
	m_fixture = m_body->CreateFixture(&fix);

	
}


