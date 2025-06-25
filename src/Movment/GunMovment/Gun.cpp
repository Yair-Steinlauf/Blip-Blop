#include "Movment/GunMovment/Gun.h"
#include "Movment/MoveComponent.h"
#include "Player.h"

Gun::Gun(AnimationSet animationSet)
	: m_weaponType(animationSet)
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

	// ירי ימינה רגיל
	if (angle > -22.5f && angle <= 22.5f) {
		m_gunDirection = { 1.f, 0.f };
		return (Direction::Right);
	}

		// ירי ימינה למעלה (זווית חדה)
	if (angle > -67.5f && angle <= -22.5f) {
		m_gunDirection = { 1.f, -1.f };
		return(Direction::UpRight);
	}

	// ירי ימינה אלכסון למעלה (כמעט מעל)
	if (angle <= -67.5f && angle > -112.5f) {
		m_gunDirection = { 0.f, -1.f };
		return(Direction::UpHeadRight);
	}

	// ירי ימינה למטה (זווית חדה)
	if (angle > 22.5f && angle <= 67.5f) {
		m_gunDirection = { 1.f, 1.f };
		return(Direction::DownRight);
	}

	// ירי ימינה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f) {
		m_gunDirection = { 0.f, 1.f };
		return(Direction::DownHeadRight);
	}

	// ירי שמאלה רגיל
	if (angle > 157.5f || angle <= -157.5f) {
		m_gunDirection = { -1.f, 0.f };
		return(Direction::Left);
	}

	// ירי שמאלה למעלה (זווית חדה)
	if (angle > -157.5f && angle <= -112.5f) {
		m_gunDirection = { -1.f, -1.f };
		return(Direction::UpLeft);
	}

	// ירי שמאלה אלכסון למעלה (כמעט מעל)
	if (angle <= -112.5f && angle > -157.5f){
		m_gunDirection = { -1.f, -1.f };
		return(Direction::UpHeadLeft);
	}

	// ירי שמאלה למטה (זווית חדה)
	if (angle > 112.5f && angle <= 157.5f){
		m_gunDirection = { -1.f, 1.f };
		return(Direction::DownLeft);
	}

	// ירי שמאלה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f) {
		m_gunDirection = { -1.f, 1.f };
		return(Direction::DownHeadLeft);
	}

	return Direction::Nan;
}

std::unique_ptr<BaseEntity> Gun::shoot(sf::Vector2f mousePos, sf::Vector2f entityPos, b2World* world) {
	if (m_timeSinceLastShot < m_shootCooldown)
		return nullptr; // עדיין לא עבר מספיק זמן
	m_timeSinceLastShot = 0.0f;

	sf::Vector2f pos = entityPos;
	sf::Vector2f direction = mousePos - pos;
	
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		sf::Vector2f dirNormalized = direction / length;
		float gunLength = 36.f; // המרחק מהמרכז לפתח הרובה

		sf::Vector2f bulletPos = (pos + dirNormalized * gunLength);
		auto bullet = Factory::instance().create(ObjectType::BULLET, sfPos{ bulletPos.x, bulletPos.y}, world);
		bullet->setDirection(m_gunDirection);
		return bullet;
	}
	return nullptr;
}

void Gun::update(float deltaTime) {
	m_timeSinceLastShot += deltaTime;
}