#include "PlayerStandMovment.h"
#include "PlayerRightMovment.h"
#include "PlayerLeftMovment.h"






void StandMovement::enter(MovingEntity& entity)
{
	entity.setDirection({ 0.f, 0.f }); // Stop movement

}

std::unique_ptr<MovingState> StandMovement::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<RightMovment>();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return std::make_unique<LeftMovment>();
	}
	return nullptr;
}
