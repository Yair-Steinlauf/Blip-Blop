#include "Player.h"
#include "Factory.h"
#include "DataLoader.h"
#include "GamePlay.h"

static auto registerIt = Factory::instance().registerType(
	ObjectType::PLAYER,
	[](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
	{
		return std::make_unique<Player>(pos, world);
	}
);

Player::Player(sfPos pos, b2World* world)
	: BaseEntity(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite),pos, world),
	m_moveComponent(*this)
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
	m_moveComponent.setEntityPos(this->getPosition());
	m_moveComponent.setMouseWorldPosition(m_gamePlay->getMouseWorldPosition());
}

void Player::setGamePlay(GamePlay* gamePlay) {
	m_gamePlay = gamePlay;
}
