#include "PlayerLeftMovment.h"	
#include "PlayerRightMovment.h"
#include "Movment/PlayerStandMovment.h"
#include "PlayerJumpMovment.h"



void PlayerLeftMovement::enter()
{
	m_moveComponent.setDirection({ -1.f, 0.f }); // Move left
}

std::unique_ptr<MovingState> PlayerLeftMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<PlayerRightMovement>(m_moveComponent);
	}
	if (m_moveComponent.checkIsGrounded() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		return std::make_unique<PlayerJumpMovement>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return nullptr;
	return std::make_unique<PlayerStandMovement>(m_moveComponent);
}
