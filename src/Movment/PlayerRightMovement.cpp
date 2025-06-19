#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"
#include "Movment/PlayerStandMovment.h"

#include "PlayerJumpMovment.h"

void PlayerRightMovement::enter()
{
    
	m_moveComponent.setDirection({ 1.f, 0.f }); // Move right
}

std::unique_ptr<MovingState> PlayerRightMovement::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return std::make_unique<PlayerLeftMovement>(m_moveComponent);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_moveComponent.checkIsGrounded())
        return std::make_unique<PlayerJumpMovement>(m_moveComponent);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return nullptr; 

    return std::make_unique<PlayerStandMovement>(m_moveComponent);
}

