#include "Player.h"
#include "Factory.h"
#include "DataLoader.h"
#include "PlayerStandMovment.h"
#include "GamePlay.h"
#include <GunMovment/SingleShotStrategy.h>
#include <GunMovment/TripleShotStrategy.h>
#include <BaseEnemy.h>

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
	m_gun(std::make_unique<Gun>(AnimationSet::ShotgunChar, std::make_unique<SingleShotStrategy>(), SIMPLE_SHOOT_TIME, DataLoader::getInstance().getSound(ObjectType::DeafultWeaponSound)))
{
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(AnimationSet::Blip, Direction::Right, 0);

	setTextureRect(frame,PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);
	m_lifeBar.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::characterSprite));
}

void Player::update(float deltaTime)
{
	if (m_moveComponent.getHealth() <= 0) {
		// TODO :: WHY HERE IS OVER
		m_gamePlay->gameOver(1500, GameOverScreen::GameResult::Defeat);
	}
	if (m_hitted) {
		m_unTouchable = true;
		m_unTouchableTimer = PLAYER_UNTOUCHABLE_TIME;
		m_hitted = false;
	}
	if (m_unTouchable) {
		m_unTouchableTimer -= deltaTime;

		if (m_unTouchableTimer <= 0) {
			m_unTouchable = false;
			m_unTouchableTimer = 0.0f;
		}
	}
	
	
	BaseEntity::update(deltaTime);
	m_moveComponent.update(deltaTime);
	m_gun->update(deltaTime);

	/* ---------- הגבלת תנועה בתוך גבולות ---------- */
	static constexpr float EDGE_MARGIN = 8.f;            
	static constexpr float PPM = 32.f;           

	b2Body* body = getBody();                            
	if (body)
	{
		b2Vec2 vel = body->GetLinearVelocity();
		b2Vec2 pos = body->GetPosition();                

		float pixX = pos.x * PPM;                        

		bool clamped = false;

		if (pixX < m_boundLeft)                          
		{
			pixX = m_boundLeft + EDGE_MARGIN;
			vel.x = 0.f;                                
			clamped = true;
		}
		else if (pixX > m_boundRight)                    
		{
			pixX = m_boundRight - EDGE_MARGIN;
			vel.x = 0.f;
			clamped = true;
		}

		if (clamped)                                     
		{
			pos.x = pixX / PPM;
			body->SetTransform(pos, body->GetAngle());
			body->SetLinearVelocity(vel);
			sync();                                      
		}
	}
	/* ------------------------------------------------ */

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
	sf::FloatRect bounds = m_lifeBar.getLocalBounds();
	m_lifeBar.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	sf::Vector2u windowSize = window.getSize();
	m_lifeBar.setPosition(50, 50);
	window.draw(m_lifeBar);
}

void Player::addLife(int life) {
	if (life < 0 && m_unTouchable) {
		return;
	}
	int currentHealth = m_moveComponent.getHealth();
	int newHealth = currentHealth + life;

	// הגבל בין 0 ל-5
	if (newHealth < 0) newHealth = 0;
	if (newHealth > 5) newHealth = 5;

	m_moveComponent.setHealth(newHealth);
}

void Player::setGun(std::unique_ptr<ShootingStrategy> strategy, AnimationSet weaponType, float shootCooldown, const sf::Sound& shootSound) {
	if (m_gun) {
		m_gun->setStrategy(std::move(strategy));
		m_gun->setAnimationSet(weaponType);
		m_gun->setshootCooldown(shootCooldown);
		m_gun->setShootSound(shootSound);
	}
}

void Player::onCollisionEnter(BaseEntity* other)
{
	if (auto* player = dynamic_cast<BaseEnemy*>(other)) {
		if (!m_unTouchable) {
			m_hitted = true;

		}
	}
}

/*------------------------------------------------------------*/
void Player::setMovementBounds(float left, float right)      // <<<
{
	m_boundLeft = left;
	m_boundRight = right;
}
void Player::clearMovementBounds()                           // <<<
{
	m_boundLeft = -std::numeric_limits<float>::infinity();
	m_boundRight = std::numeric_limits<float>::infinity();
}

/*--------------------------- שאר הפונקציות ללא שינוי ------------------*/