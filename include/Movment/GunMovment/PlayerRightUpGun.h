#pragma once
#include <memory>
#include "GunState.h"

class PlayerRightUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};