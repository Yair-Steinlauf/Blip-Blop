#include "PlayerLeftMovment.h"	
#include "PlayerRightMovment.h"
#include "Movment/PlayerStandMovment.h"




void LeftMovment::enter(MovingEntity& entity)
{
	entity.setDirection({ -1.f, 0.f }); // Move left
}

std::unique_ptr<MovingState> LeftMovment::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<RightMovment>();
	}
	return std::make_unique<StandMovement>();
}
