#include <Platform.h>

Platform::Platform(sfPos pos, b2World* world, sf::Vector2f size)
    : BaseEntity(nullptr, pos, world)
{
    initBox2d(pos, size);
}

Platform::Platform(const std::vector<sf::Vector2f>& points, b2World* world)
    : BaseEntity(nullptr, {}, world)
{
    initChainShapeBox2d(points);
}

void Platform::initBox2d(sfPos pos, sf::Vector2f size)
{
    initBody(pos);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2 / SCALE, size.y / 2 / SCALE);

    b2FixtureDef fix;
    fix.shape = &polygonShape;
    fix.friction = 0.4f;
    fix.restitution = 0.1f;
    fix.density = 0.0f;

    m_body->CreateFixture(&fix);
}

void Platform::initChainShapeBox2d(const std::vector<sf::Vector2f>& points)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    m_body = m_world->CreateBody(&bodyDef);

    for (size_t i = 1; i < points.size(); ++i) {
        b2EdgeShape edge;

        b2Vec2 v1(points[i - 1].x / SCALE, points[i - 1].y / SCALE);
        b2Vec2 v2(points[i].x / SCALE, points[i].y / SCALE);

        // מגדירים את הקצוות ישירות (אין צורך ב־Set או בשדות נוספים)
        edge.m_vertex1 = v1;
        edge.m_vertex2 = v2;

        b2FixtureDef fix;
        fix.shape = &edge;
        fix.friction = 0.4f;
        fix.restitution = 0.1f;
        fix.density = 0.0f;

        m_body->CreateFixture(&fix);
    }
}


