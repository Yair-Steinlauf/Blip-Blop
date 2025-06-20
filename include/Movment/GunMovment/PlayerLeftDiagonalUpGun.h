#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerLeftDiagonalUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDiagonalUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};