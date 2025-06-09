#include "RightMovment.h"
#include "LeftMovment.h"
#include "Movment/StandMovment.h"


void RightMovment::enter(MovingEntity& entity)
{
	entity.setDirection({ 1.f, 0.f }); // Move right
}

std::unique_ptr<MovingState> RightMovment::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return std::make_unique<LeftMovment>();
	}
	return std::make_unique<StandMovement>();
}
