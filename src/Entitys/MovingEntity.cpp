#include "MovingEntity.h"
#include "Movment/MovingState.h"
MovingEntity::MovingEntity(sfPos pos, b2World* world) :
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

MovingEntity& MovingEntity::setVelocity(float x, float y)
{
	m_body->SetLinearVelocity(b2Vec2(x, y));
	return *this;
}

void MovingEntity::update(float deltaTime)
{
	movment();
	if (checkIsGrounded()) {
		// על הקרקע - כוח מלא
		b2Vec2 force(m_direction.x * m_speed * 10.0f, 0);
		m_body->ApplyForceToCenter(force, true);
	}
	else {
		// ✅ באוויר - כוח חלש מאוד!
		b2Vec2 airForce(m_direction.x * m_speed * 2.0f, 0); // פי 5 פחות!
		m_body->ApplyForceToCenter(airForce, true);
	}

	/*movment();
	b2Vec2 force(m_direction.x * m_speed * 10.0f, 0);
	m_body->ApplyForceToCenter(force, true);
	*/sync();
}

void MovingEntity::movment()
{
	if (m_movement)
	{
		auto newState = m_movement->move();
		if (newState)
		{
			m_movement = std::move(newState);
			m_movement->enter();
		}
	}
}

MovingEntity& MovingEntity::applyJumpImpulse(float force)
{
	if (checkIsGrounded()) {
		b2Vec2 jumpImpulse(0, -force);
		m_body->ApplyLinearImpulseToCenter(jumpImpulse, true);
	}
	return *this;
}

bool MovingEntity::checkIsGrounded() const
{
	return std::abs(m_body->GetLinearVelocity().y) < 0.5f;
}

void MovingEntity::initBox2d(sfPos pos)
{
	BaseEntity::initBox2d(pos);
	b2FixtureDef fix;
	fix.shape = &m_polygonShape;
	fix.density = 1.0f;
	fix.friction = 0.8f;
	fix.restitution = 0.0f;

	m_fixture = m_body->CreateFixture(&fix);
	m_body->SetFixedRotation(true);
	m_body->SetLinearDamping(1);

}


