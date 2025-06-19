#include "Platform.h"	
#include "Factory/Factory.h"

static auto registerIt = Factory::instance().registerType(
    ObjectType::PLATFORM,
    [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
    {
        return std::make_unique <Platform> (pos, world);
    }
);

Platform::Platform(sfPos pos, b2World* world, sf::Vector2f size)
	:BaseEntity(nullptr, pos, world)
{
    initBox2d(pos, size);
}

void Platform::initBox2d(sfPos pos, sf::Vector2f size)
{
	BaseEntity::initBox2d(pos);
	b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2 / SCALE, size.y / 2 / SCALE);

    b2FixtureDef fix;
    fix.shape = &polygonShape;
    fix.friction = 0.4f;
    fix.restitution = 0.1f;
    fix.density = 0.0f;
    m_body->CreateFixture(&fix);
}
