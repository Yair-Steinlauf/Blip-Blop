#pragma once
#include <memory>
#include "GunState.h"

class PlayerLeftUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};