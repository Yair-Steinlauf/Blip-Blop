#include "BaseEnemy.h"
#include "Player.h"
#include "EnemyMovmentState.h"

BaseEnemy::BaseEnemy(sf::Texture* tex, sfPos pos, b2World* world, Player* player, AnimationSet animationSet)
	:BaseEntity(tex, pos, world), m_player(player), m_moveComponent(*this, nullptr),
    m_animation(Animator(m_sprite, m_animationSet)),m_animationSet(animationSet)
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
void BaseEnemy::update(float deltaTime)
{
	BaseEntity::update(deltaTime);
	m_moveComponent.update(deltaTime);
    m_animation.setDirection(posToDirection(m_moveComponent.getDirection()));
    m_animation.update(deltaTime);
}
