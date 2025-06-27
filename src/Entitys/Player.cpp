#include "Player.h"
#include "Factory.h"
#include "DataLoader.h"
#include "PlayerStandMovment.h"
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
	m_moveComponent(*this, std::make_unique<PlayerStandMovement>(m_moveComponent)), 
	m_gun(std::make_unique<Gun>(AnimationSet::Blip, std::make_unique<SingleShotStrategy>(), SINGLE_SHOOT_TIME, DataLoader::getInstance().getSound(ObjectType::shotGunSound)))
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::Blip, Direction::Right, 0);

	setTextureRect(frame,PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);
	m_lifeBar.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::characterSprite));
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

void Player::updateLifeBarSprite()
{
	int life = m_moveComponent.getHealth();

	Direction healthDirection = static_cast<Direction>(static_cast<int>(Direction::Health0) + life);

	const sf::IntRect& frame = GameAnimations::getInstance()
		.getFrame(AnimationSet::playerHPFrames, healthDirection, 0);

	m_lifeBar.setTextureRect(frame);
}

void Player::drawLifeBar(sf::RenderWindow& window)
{
	updateLifeBarSprite();
	// 1. îîøëæ àú äñôøééè ìôé âåãì äúîåðä
	sf::FloatRect bounds = m_lifeBar.getLocalBounds();
	m_lifeBar.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// 2. îî÷í àåúå áîøëæ äçìåï
	sf::Vector2u windowSize = window.getSize();
	m_lifeBar.setPosition(50, 50);
	window.draw(m_lifeBar);
}

void Player::addLife(int life) {
		int neww = m_moveComponent.getHealth() + life;
		if (neww <= 5)
			m_moveComponent.setHealth(neww);
}

void Player::setGun(std::unique_ptr<ShootingStrategy> strategy, AnimationSet weaponType, float shootCooldown, const sf::Sound& shootSound) {
	if (m_gun) {
		m_gun->setStrategy(std::move(strategy));
		m_gun->setAnimationSet(weaponType);
		m_gun->setshootCooldown(shootCooldown);
		m_gun->setShootSound(shootSound);
	}
}
