#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"
#include "Movment/PlayerStandMovment.h"

#include "PlayerJumpMovment.h"

void PlayerRightMovement::enter()
{
	m_entity.setDirection({ 1.f, 0.f }); // Move right
}

std::unique_ptr<MovingState> PlayerRightMovement::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return std::make_unique<PlayerLeftMovement>(m_entity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_entity.checkIsGrounded())
        return std::make_unique<PlayerJumpMovement>(m_entity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return nullptr; // äîùê éîéï

    return std::make_unique<PlayerStandMovement>(m_entity);
}
