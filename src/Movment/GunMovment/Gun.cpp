#include "Movment/GunMovment/Gun.h"
#include "Movment/MoveComponent.h"
#include "Player.h"

Gun::Gun(AnimationSet animationSet, Player* owner)
	: m_weaponType(animationSet), m_owner(owner)
{
}

void Gun::enter(Direction direction)
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(m_weaponType, direction, 0);

	m_owner->setTextureRect(frame, PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);	
}

Direction Gun::move(sf::Vector2f mousePos, sf::Vector2f entityPos) {
	sf::Vector2f delta = mousePos - entityPos;
	const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

	// ירי ימינה רגיל
	if (angle > -22.5f && angle <= 22.5f)
		return (Direction::Right);

		// ירי ימינה למעלה (זווית חדה)
	if (angle > -67.5f && angle <= -22.5f)
		return(Direction::UpRight);

	// ירי ימינה אלכסון למעלה (כמעט מעל)
	if (angle <= -67.5f && angle > -112.5f)
		return(Direction::UpHeadRight);

	// ירי ימינה למטה (זווית חדה)
	if (angle > 22.5f && angle <= 67.5f)
		return(Direction::DownRight);

	// ירי ימינה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f)
		return(Direction::DownHeadRight);

	// ירי שמאלה רגיל
	if (angle > 157.5f || angle <= -157.5f)
		return(Direction::Left);

	// ירי שמאלה למעלה (זווית חדה)
	if (angle > -157.5f && angle <= -112.5f)
		return(Direction::UpLeft);

	// ירי שמאלה אלכסון למעלה (כמעט מעל)
	if (angle <= -112.5f && angle > -157.5f)
		return(Direction::UpHeadLeft);

	// ירי שמאלה למטה (זווית חדה)
	if (angle > 112.5f && angle <= 157.5f)
		return(Direction::DownLeft);

	// ירי שמאלה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f)
		return(Direction::DownHeadLeft);

	return Direction::Nan;
}

void Gun::shoot(sf::Vector2f mousePos, sf::Vector2f entityPos) {
	sf::Vector2f pos = entityPos;
	sf::Vector2f direction = mousePos - pos;
	
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		sf::Vector2f dirNormalized = direction / length;
		float gunLength = 36.f; // המרחק מהמרכז לפתח הרובה

		std::cout << (pos + dirNormalized * gunLength).x;
	}
}