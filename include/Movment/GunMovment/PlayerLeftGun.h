#pragma once
#include "Movment/GunMovment/GunState.h"

class PlayerLeftGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};