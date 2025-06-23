#pragma once
#include <memory>
#include "Movment/GunMovment/GunState.h"

class PlayerRightDiagonalDownGun : public GunState
{
public:
	using GunState::GunState;

	~PlayerRightDiagonalDownGun() override = default;
	void enter() override;
	std::unique_ptr<GunState> move(sf::Vector2f mousePos, sf::Vector2f entityPos) override;
};