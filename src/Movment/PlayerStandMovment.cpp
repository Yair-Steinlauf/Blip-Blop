#include "PlayerStandMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"

#include "PlayerJumpMovment.h"



void PlayerStandMovement::enter()
{
	m_moveComponent.setDirection({ 0.f, 0.f }); // Stop movement
}

std::unique_ptr<MovingState> PlayerStandMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<PlayerRightMovement>(m_moveComponent);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return std::make_unique<PlayerLeftMovement>(m_moveComponent);
	}
	else if (m_moveComponent.checkIsGrounded() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		return std::make_unique<PlayerJumpMovement>(m_moveComponent);
	}
	return nullptr;
	//return std::make_unique<PlayerStandMovement>(m_entity);

}


