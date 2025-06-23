#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerRightUpGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightUpGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move(sf::Vector2f mousePos, sf::Vector2f entityPos) override;
};