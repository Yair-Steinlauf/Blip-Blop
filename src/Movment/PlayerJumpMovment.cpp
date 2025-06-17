#include "PlayerJumpMovment.h"
#include "PlayerLeftMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerStandMovment.h"


void PlayerJumpMovement::enter()
{
	if (m_entity.checkIsGrounded()) {
		m_entity.setDirection({ 0.f, 0.f });
		m_entity.applyJumpImpulse(300.f);
	}
}


std::unique_ptr<MovingState> PlayerJumpMovement::move()
{
	//TODO: fast sinking
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	//	return std::make_unique<PlayerStandMovement>();
	//}
	if (m_entity.checkIsGrounded())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			return std::make_unique<PlayerLeftMovement>(m_entity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			return std::make_unique<PlayerRightMovement>(m_entity);
		}

	return nullptr;

	}
	return std::make_unique<PlayerStandMovement>(m_entity);


}