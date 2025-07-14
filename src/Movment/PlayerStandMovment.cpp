#include "PlayerStandMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"

#include "PlayerJumpMovment.h"



void PlayerStandMovement::enter()
{
	m_moveComponent.setDirection({ 0.f, 0.f });


}

std::unique_ptr<MovingState> PlayerStandMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return std::make_unique<PlayerRightMovement>(m_moveComponent);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return std::make_unique<PlayerLeftMovement>(m_moveComponent);
	}
	else if (m_moveComponent.checkIsGrounded() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		return std::make_unique<PlayerJumpMovement>(m_moveComponent);
	}
	return nullptr;


}


