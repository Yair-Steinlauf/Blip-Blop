#include "Bullet.h"
#include <Player.h>

static auto registerIt = Factory::instance().registerType(
	ObjectType::BULLET,
	[](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
	{
		return std::make_unique<Bullet>(pos, world);
	}
);

Bullet::Bullet(sfPos pos, b2World* world)
	: BaseEntity(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world)
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::RifleGunBull, Direction::Right, 0);

	 setTextureRect(frame);

	this->setFixtureForMov();
}

void Bullet::update(float deltaTime) {
	m_lifetime += deltaTime;

	if (m_lifetime >= BULLET_LIFETIME)
		markForRemoval();

	b2Vec2 newVel(m_direction.x * BULLET_SPEED, m_direction.y * BULLET_SPEED);
	this->getBody()->SetLinearVelocity(newVel);
	BaseEntity::update(deltaTime);
}

void Bullet::onCollisionEnter(BaseEntity* other){
	if (/*dynamic_cast<Player*>(other) || */dynamic_cast<Player*>(other)) {
		markForRemoval();
	}
}