#pragma once
#include <memory>
#include "GunState.h"

class PlayerLeftDiagonalUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDiagonalUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};