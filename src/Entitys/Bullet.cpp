#include "Bullet.h"

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
		.getFrame(AnimationSet::Blip, Direction::Right, 0);

	setTextureRect(frame, PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);

	this->setFixtureForBullet();
}

void Bullet::update(float deltaTime) {
	float desiredSpeed = 8.0f;
	b2Vec2 newVel(m_direction.x * desiredSpeed, m_direction.y * desiredSpeed);
	this->getBody()->SetLinearVelocity(newVel);
	BaseEntity::update(deltaTime);
}
