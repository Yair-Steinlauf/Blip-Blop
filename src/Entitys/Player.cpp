#include "Player.h"

static auto registerIt = Factory<MovingEntity>::instance().registerType(
	ObjectType::Player,
	[]() -> std::unique_ptr<MovingEntity>
	{
		return std::make_unique<Player>();
	}
);
