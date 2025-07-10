#include "BaseEnemy.h"
#include "Player.h"
#include "EnemyMovmentState.h"
#include "bullet.h"

BaseEnemy::BaseEnemy(sf::Texture* tex, sfPos pos, b2World* world, Player* player, AnimationSet animationSet)
	:BaseEntity(tex, pos, world), m_player(player), m_moveComponent(*this, nullptr),
	m_animation(Animator(m_sprite, m_animationSet)), m_animationSet(animationSet)
{
	if (!m_player) {
		throw std::runtime_error("BaseEnemy needs a valid Player!");
	}

	auto enemyState = std::make_unique<EnemyMovementState>(
		m_moveComponent,
		[this]() -> sfPos {
			return m_player->getPosition();
		}
	);
	m_moveComponent.setSpeed(10);//TODO: לשפר את זה, המהירות מוזרה?
	m_moveComponent.setState(std::move(enemyState));
	const sf::IntRect& frame =
		GameAnimations::getInstance()
		.getFrame(m_animationSet, Direction::Right, 0);

	setTextureRect(frame, PLAYER_FIXTURE_WIDTH, PLAYER_FIXTURE_HEIGHT);
}


void BaseEnemy::addLife(int life) {
	int neww = m_moveComponent.getHealth() + life;
	if (neww <= 5)
		m_moveComponent.setHealth(neww);
}

void BaseEnemy::onCollisionEnter(BaseEntity* other)
{
	if (auto* bullet = dynamic_cast<Bullet*>(other)) {
		// נזק לאויב
		m_moveComponent.takeDamage(1);
	}
    if (auto* player = dynamic_cast<Player*>(other)) {
		player->addLife(-1);
    }
}


void BaseEnemy::update(float deltaTime)
{
    BaseEntity::update(deltaTime);

    if (m_isExploding) {
        updateExplosionAnimation(deltaTime);
    }
    else if (m_moveComponent.getHealth() <= 0)
    {
        startExplosion();
    }
    else {
        m_moveComponent.update(deltaTime);
        m_animation.setDirection(posToDirection(m_moveComponent.getDirection()));
        m_animation.update(deltaTime);
    }
}

void BaseEnemy::startExplosion() {
    m_isExploding = true;
    m_explosionTime = 0.0f;
    m_currentExplosionFrame = 0;
    m_animation.setDirection(Direction::Stay);



    m_animation.setLoop(false); // לא לולאה
    m_animation.reset();        // התחלה מהתחלה
    if (m_body) {
        m_body->SetLinearVelocity(b2Vec2(0, 0));
        m_body->SetType(b2_staticBody);
    }
}

void BaseEnemy::updateExplosionAnimation(float deltaTime) {
    m_animation.update(deltaTime);
    if (m_animation.isFinished()) {
        markForRemoval();
    }
}

