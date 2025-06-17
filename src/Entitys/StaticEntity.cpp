#include "StaticEntity.h"

StaticEntity::StaticEntity(sfPos pos, b2World* world, sf::Vector2f size)
	:BaseEntity(pos, world)
{
	m_bodyDef.type = b2_staticBody;
    initBox2d(pos, size);
}


void StaticEntity::initBox2d(sfPos pos, sf::Vector2f size)
{
    std::cout << "b2Body created at: ("
        << m_bodyDef.position.x * SCALE << ", "
        << m_bodyDef.position.y * SCALE << ")\n";

    m_bodyDef.position = { pos.x / SCALE, pos.y / SCALE };
    m_body = m_world->CreateBody(&m_bodyDef);

    m_polygonShape.SetAsBox(size.x / 2 / SCALE, size.y / 2 / SCALE);

    b2FixtureDef fix;
    fix.shape = &m_polygonShape;
    fix.friction = 0.8f;
    fix.restitution = 0.1f;
    fix.density = 0.0f;
    m_fixture = m_body->CreateFixture(&fix);
}
