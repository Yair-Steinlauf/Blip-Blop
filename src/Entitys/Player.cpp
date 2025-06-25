#include "Player.h"
#include "Factory.h"
#include "DataLoader.h"
#include "GamePlay.h"
#include <GunMovment/SingleShotStrategy.h>
#include <GunMovment/TripleShotStrategy.h>

static auto registerIt = Factory::instance().registerType(
	ObjectType::PLAYER,
	[](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
	{
		return std::make_unique<Player>(pos, world);
	}
);

Player::Player(sfPos pos, b2World* world)
	: BaseEntity(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite),pos, world),
	m_moveComponent(*this), m_gun(std::make_unique<Gun>(AnimationSet::Blip, std::make_unique<SingleShotStrategy>(), 0.2f))
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::Blip, Direction::Right, 0);

	setTextureRect(frame,PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);
}

void Player::update(float deltaTime)
{
	BaseEntity::update(deltaTime);
	m_moveComponent.update(deltaTime);
	m_gun->update(deltaTime);

	if (m_gun) {
		Direction direction = m_gun->move(m_gamePlay->getMouseWorldPosition(), this->getPosition());
		if (static_cast<int>(direction) != 0)
			m_gun->enter(direction, this);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto bullets = m_gun->shoot(m_gamePlay->getMouseWorldPosition(), this->getPosition(), this->getWorld());
			for (auto& bullet : bullets)
				m_gamePlay->addEntity(std::move(bullet));
		}
	}
}

void Player::setGamePlay(GamePlay* gamePlay) {
	m_gamePlay = gamePlay;
}
