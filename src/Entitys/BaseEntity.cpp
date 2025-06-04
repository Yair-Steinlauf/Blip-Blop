#include "BaseEntity.h"

void BaseEntity::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
