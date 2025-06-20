#pragma once
#include <memory>
#include "GunState.h"

class PlayerLeftDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerLeftDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move() override;
};