#include "Movment/GunMovment/Gun.h"
#include "Movment/MoveComponent.h"
#include "Player.h"
#include "Movment/GunMovment/ShootingStrategy.h"

Gun::Gun(AnimationSet animationSet, std::unique_ptr<ShootingStrategy> strategy, float shootCooldown, const sf::Sound& shootSound)
	: m_weaponType(animationSet),
	m_strategy(std::move(strategy)),
	m_shootCooldown(shootCooldown),
	m_timeSinceLastShot(0.f),
	m_shootSound(shootSound)
{
}


void Gun::enter(Direction direction, Player* owner)
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(m_weaponType, direction, 0);

	owner->setTextureRect(frame, PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);	
}

Direction Gun::move(sf::Vector2f mousePos, sf::Vector2f entityPos) {
	sf::Vector2f delta = mousePos - entityPos;
	const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

	// ��� ����� ����
	if (angle > -22.5f && angle <= 22.5f) {
		m_gunDirection = { 1.f, 0.f };
		return (Direction::Right);
	}

		// ��� ����� ����� (����� ���)
	if (angle > -67.5f && angle <= -22.5f) {
		m_gunDirection = { 1.f, -1.f };
		return(Direction::UpRight);
	}

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -67.5f && angle > -112.5f) {
		m_gunDirection = { 0.f, -1.f };
		return(Direction::UpHeadRight);
	}

	// ��� ����� ���� (����� ���)
	if (angle > 22.5f && angle <= 67.5f) {
		m_gunDirection = { 1.f, 1.f };
		return(Direction::DownRight);
	}

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f) {
		m_gunDirection = { 0.f, 1.f };
		return(Direction::DownHeadRight);
	}

	// ��� ����� ����
	if (angle > 157.5f || angle <= -157.5f) {
		m_gunDirection = { -1.f, 0.f };
		return(Direction::Left);
	}

	// ��� ����� ����� (����� ���)
	if (angle > -157.5f && angle <= -112.5f) {
		m_gunDirection = { -1.f, -1.f };
		return(Direction::UpLeft);
	}

	// ��� ����� ������ ����� (���� ���)
	if (angle <= -112.5f && angle > -157.5f){
		m_gunDirection = { -1.f, -1.f };
		return(Direction::UpHeadLeft);
	}

	// ��� ����� ���� (����� ���)
	if (angle > 112.5f && angle <= 157.5f){
		m_gunDirection = { -1.f, 1.f };
		return(Direction::DownLeft);
	}

	// ��� ����� ������ ���� (���� ����)
	if (angle > 67.5f && angle <= 112.5f) {
		m_gunDirection = { -1.f, 1.f };
		return(Direction::DownHeadLeft);
	}

	return Direction::Nan;
}

std::vector<std::unique_ptr<BaseEntity>> Gun::shoot(sf::Vector2f mousePos, sf::Vector2f entityPos, b2World* world) {
	if (m_timeSinceLastShot < m_shootCooldown)
		return {};

	m_timeSinceLastShot = 0.0f;
	sf::Vector2f direction = mousePos - entityPos;
	m_shootSound.play();
	return m_strategy->shoot(entityPos, m_gunDirection, world);
}

void Gun::update(float deltaTime) {
	m_timeSinceLastShot += deltaTime;
}

void Gun::setStrategy(std::unique_ptr<ShootingStrategy> strategy) {
	m_strategy = std::move(strategy);
}

void Gun::setAnimationSet(AnimationSet set) {
	m_weaponType = set;
}

void Gun::setshootCooldown(float shootCooldown){
	m_shootCooldown = shootCooldown;
}

void Gun::setShootSound(const sf::Sound& sound) {
	m_shootSound = sound;
}
