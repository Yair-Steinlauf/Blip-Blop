#include "Movment/GunMovment/Gun.h"
#include "Movment/MoveComponent.h"
Gun::Gun(MoveComponent& moveComponent)
	: m_moveComponent(moveComponent)
{
}

void Gun::enter(Direction direction)
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::Blip, direction, 0);

	m_moveComponent.getEntity().setTextureRect(frame, PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);
}

Direction Gun::move(sf::Vector2f mousePos, sf::Vector2f entityPos) {
	sf::Vector2f delta = mousePos - entityPos;
	const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	//	Direction::Shoot
	//}

	// ��� ����� ����
	if (angle > -22.5f && angle <= 22.5f)
		return (Direction::Right);

		// ��� ����� ����� (����� ���)
	if (angle > -67.5f && angle <= -22.5f)
		return(Direction::UpRight);

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -67.5f && angle > -112.5f)
		return(Direction::UpHeadRight);

	// ��� ����� ���� (����� ���)
	if (angle > 22.5f && angle <= 67.5f)
		return(Direction::DownRight);

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f)
		return(Direction::DownHeadRight);

	// ��� ����� ����
	if (angle > 157.5f || angle <= -157.5f)
		return(Direction::Left);

	// ��� ����� ����� (����� ���)
	if (angle > -157.5f && angle <= -112.5f)
		return(Direction::UpLeft);

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -112.5f && angle > -157.5f)
		return(Direction::UpHeadLeft);

	// ��� ����� ���� (����� ���)
	if (angle > 112.5f && angle <= 157.5f)
		return(Direction::DownLeft);

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f)
		return(Direction::DownHeadLeft);

	return Direction::Nan;
}

