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
#include <GunMovment/GunShoot.h>


void GunShoot::enter()
{
	sf::Vector2f pos = m_moveComponent.getEntity().getPosition();
	sf::Vector2f direction = m_moveComponent.getMouseWorldPosition() - pos;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		sf::Vector2f dirNormalized = direction / length;
		float gunLength = 36.f; // המרחק מהמרכז לפתח הרובה

		std::cout << (pos + dirNormalized * gunLength).x;
	}

	std::cout << (pos ).x;
}

std::unique_ptr<GunState> GunShoot::move(sf::Vector2f mousePos, sf::Vector2f entityPos)
{
	sf::Vector2f delta = mousePos - entityPos;
	const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return std::make_unique<GunShoot>(m_moveComponent);
	}

	// ירי ימינה רגיל
	if (angle > -22.5f && angle <= 22.5f)
		return std::make_unique<PlayerRightGun>(m_moveComponent);

	// ירי ימינה למעלה (זווית חדה)
	if (angle > -67.5f && angle <= -22.5f)
		return std::make_unique<PlayerRightUpGun>(m_moveComponent);

	// ירי ימינה אלכסון למעלה (כמעט מעל)
	if (angle <= -67.5f && angle > -112.5f)
		return std::make_unique<PlayerRightDiagonalUpGun>(m_moveComponent);

	// ירי ימינה למטה (זווית חדה)
	if (angle > 22.5f && angle <= 67.5f)
		return std::make_unique<PlayerRightDownGun>(m_moveComponent);

	// ירי ימינה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f)
		return std::make_unique<PlayerRightDiagonalDownGun>(m_moveComponent);

	// ירי שמאלה רגיל
	if (angle > 157.5f || angle <= -157.5f)
		return std::make_unique<PlayerLeftGun>(m_moveComponent);

	// ירי שמאלה למעלה (זווית חדה)
	if (angle > -157.5f && angle <= -112.5f)
		return std::make_unique<PlayerLeftUpGun>(m_moveComponent);

	// ירי שמאלה אלכסון למעלה (כמעט מעל)
	if (angle <= -112.5f && angle > -157.5f)
		return std::make_unique<PlayerLeftDiagonalUpGun>(m_moveComponent);

	// ירי שמאלה למטה (זווית חדה)
	if (angle > 112.5f && angle <= 157.5f)
		return std::make_unique<PlayerLeftDownGun>(m_moveComponent);

	// ירי שמאלה אלכסון למטה (כמעט מתחת)
	if (angle > 67.5f && angle <= 112.5f)
		return std::make_unique<PlayerLeftDiagonalDownGun>(m_moveComponent);

	return nullptr;
}