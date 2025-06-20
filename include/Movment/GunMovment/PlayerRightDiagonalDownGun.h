#pragma once
#include <memory>
#include "GunState.h"

class PlayerRightDiagonalDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightDiagonalDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};