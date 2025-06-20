#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerRightDiagonalUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightDiagonalUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};