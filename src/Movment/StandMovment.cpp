#include "PlayerStandMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"
#include "PlayerJumpMovment.h"





void PlayerStandMovement::enter()
{
	m_entity.setDirection({ 0.f, 0.f }); // Stop movement

}

std::unique_ptr<MovingState> PlayerStandMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<PlayerRightMovement>(m_entity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return std::make_unique<PlayerLeftMovement>(m_entity);
	}
	else if (m_entity.checkIsGrounded() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		return std::make_unique<PlayerJumpMovement>(m_entity);
	}
	return nullptr;
	//return std::make_unique<PlayerStandMovement>(m_entity);

}
