#include "BaseEntity.h"

void BaseEntity::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sfPos BaseEntity::getPosition() const
{
	 return m_sprite.getPosition();
}
