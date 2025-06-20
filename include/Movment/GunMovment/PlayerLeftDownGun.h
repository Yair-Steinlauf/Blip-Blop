#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerLeftDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};