#pragma once
#include "Movment/GunMovment/GunState.h"

class PlayerRightGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move(sf::Vector2f mousePos, sf::Vector2f entityPos) override;
};