#pragma once
#include "GunState.h"

class PlayerLeftGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};