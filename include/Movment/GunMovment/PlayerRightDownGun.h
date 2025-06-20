#pragma once
#include <memory>
#include "GunState.h"

class PlayerRightDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};