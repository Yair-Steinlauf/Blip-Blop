#include "PlayerLeftMovment.h"	
#include "PlayerRightMovment.h"
#include "Movment/PlayerStandMovment.h"
#include "PlayerJumpMovment.h"



void PlayerLeftMovement::enter()
{
	m_entity.setDirection({ -1.f, 0.f }); // Move left
}

std::unique_ptr<MovingState> PlayerLeftMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<PlayerRightMovement>(m_entity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		return std::make_unique<PlayerJumpMovement>(m_entity);
	}
	return std::make_unique<PlayerStandMovement>(m_entity);
}
