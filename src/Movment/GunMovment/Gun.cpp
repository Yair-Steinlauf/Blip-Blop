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
	return posToDirection(delta);
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