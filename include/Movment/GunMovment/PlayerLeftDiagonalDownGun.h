#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerLeftDiagonalDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDiagonalDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};