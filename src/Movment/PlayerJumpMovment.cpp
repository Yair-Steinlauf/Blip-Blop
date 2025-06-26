#include "PlayerJumpMovment.h"
#include "PlayerLeftMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerStandMovment.h"


void PlayerJumpMovement::enter()
{
	if (m_moveComponent.checkIsGrounded()) {
		m_moveComponent.applyJumpImpulse(10.f);
	}
}


std::unique_ptr<MovingState> PlayerJumpMovement::move()
{
	//TODO: fast sinking
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	//	return std::make_unique<PlayerStandMovement>(m_moveComponent);
	//}
	if (m_moveComponent.checkIsGrounded())
	{
		return std::make_unique<PlayerStandMovement>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return std::make_unique<PlayerLeftMovement>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return std::make_unique<PlayerRightMovement>(m_moveComponent);
	}
	return nullptr;
}