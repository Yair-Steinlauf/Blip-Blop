#include "Strategy/PlayerRegularMove.h"
#include "MovingEntity.h"
#include <cmath>

sf::Vector2f PlayerRegularMove::setDirection(MovingEntity& entity, float deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
	//support WASD and Arrow keys, and diagnoal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += 1.f;

    if (movement.x != 0.f && movement.y != 0.f)
    {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;
    }

    movement *= m_speed * deltaTime;

    sf::Vector2f currentPos = entity.getPosition();
    return currentPos + movement;
} 