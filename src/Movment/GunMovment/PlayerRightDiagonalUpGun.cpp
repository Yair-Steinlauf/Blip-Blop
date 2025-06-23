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


void PlayerRightDiagonalUpGun::enter()
{
	std::cout << ">> PlayerRightGun::enter()\n";

	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::Blip, Direction::UpHeadRight, 0);

	m_moveComponent.getEntity().setTextureRect(frame);
}


std::unique_ptr<GunState> PlayerRightDiagonalUpGun::move(sf::Vector2f mousePos, sf::Vector2f entityPos)
{
	sf::Vector2f delta = mousePos - entityPos;
	const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

	// ��� ����� ����
	if (angle > -22.5f && angle <= 22.5f)
		return std::make_unique<PlayerRightGun>(m_moveComponent);

	// ��� ����� ����� (����� ���)
	if (angle > -67.5f && angle <= -22.5f)
		return std::make_unique<PlayerRightUpGun>(m_moveComponent);

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -67.5f && angle > -112.5f)
		return std::make_unique<PlayerRightDiagonalUpGun>(m_moveComponent);

	// ��� ����� ���� (����� ���)
	if (angle > 22.5f && angle <= 67.5f)
		return std::make_unique<PlayerRightDownGun>(m_moveComponent);

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f)
		return std::make_unique<PlayerRightDiagonalDownGun>(m_moveComponent);

	// ��� ����� ����
	if (angle > 157.5f || angle <= -157.5f)
		return std::make_unique<PlayerLeftGun>(m_moveComponent);

	// ��� ����� ����� (����� ���)
	if (angle > -157.5f && angle <= -112.5f)
		return std::make_unique<PlayerLeftUpGun>(m_moveComponent);

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -112.5f && angle > -157.5f)
		return std::make_unique<PlayerLeftDiagonalUpGun>(m_moveComponent);

	// ��� ����� ���� (����� ���)
	if (angle > 112.5f && angle <= 157.5f)
		return std::make_unique<PlayerLeftDownGun>(m_moveComponent);

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f)
		return std::make_unique<PlayerLeftDiagonalDownGun>(m_moveComponent);

	return nullptr;
}
