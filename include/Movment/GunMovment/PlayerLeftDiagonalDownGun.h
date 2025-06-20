#pragma once
#include <memory>
#include "GunState.h"

class PlayerLeftDiagonalDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDiagonalDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};