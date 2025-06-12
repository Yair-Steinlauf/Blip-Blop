#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Constance.h"

class Cube   {
private:
    b2Body* body;
public:
    sf::RectangleShape shape;
    Cube(b2World& world, float x, float y, float width = 50, float height = 50, bool isStatic = false) {
        b2BodyDef bodyDef;
        bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape box;
        box.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.5f; 
        body->CreateFixture(&fixtureDef);

        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);
        shape.setFillColor(isStatic ? sf::Color::Green : sf::Color::Red);
    }

    void update() {
        b2Vec2 pos = body->GetPosition();
        shape.setPosition(pos.x * SCALE, pos.y * SCALE);
        shape.setRotation(body->GetAngle() * 180 / b2_pi);
    }
};

