#include "Movment/GunMovment/PlayerLeftDiagonalDownGun.h"
#include "Movment/GunMovment/PlayerLeftDiagonalUpGun.h"
#include "Movment/GunMovment/PlayerLeftDownGun.h"
#include "Movment/GunMovment/PlayerLeftGun.h"
#include "Movment/GunMovment/PlayerLeftUpGun.h"
#include "Movment/GunMovment/PlayerRightDiagonalDownGun.h"
#include "Movment/GunMovment/PlayerRightDiagonalUpGun.h"
#include "Movment/GunMovment/PlayerRightDownGun.h"
#include "Movment/GunMovment/PlayerRightGun.h"
#include "Movment/GunMovment/PlayerRightUpGun.h"


void PlayerLeftDiagonalUpGun::enter()
{
	//if (m_moveComponent.checkIsGrounded()) {
	//	m_moveComponent.applyJumpImpulse(300.f);
	//}
}


std::unique_ptr<GunState> PlayerLeftDiagonalUpGun::move()
{
	sf::Vector2f right = { 1.f, 0.f };
	sf::Vector2f left = { -1.f, 0.f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return std::make_unique<PlayerRightGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_moveComponent.getDirection() == right) {
		return std::make_unique<PlayerRightUpGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_moveComponent.getDirection() == right) {
		return std::make_unique<PlayerRightDownGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_moveComponent.getDirection() == right) {
		return std::make_unique<PlayerRightDiagonalUpGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_moveComponent.getDirection() == right) {
		return std::make_unique<PlayerRightDiagonalDownGun>(m_moveComponent);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return std::make_unique<PlayerLeftGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_moveComponent.getDirection() == left) {
		return std::make_unique<PlayerLeftUpGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_moveComponent.getDirection() == left) {
		return std::make_unique<PlayerLeftDownGun>(m_moveComponent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_moveComponent.getDirection() == left) {
		return std::make_unique<PlayerLeftDiagonalDownGun>(m_moveComponent);
	}
	return nullptr;
}