#include "BaseEnemy.h"
#include "Player.h"
#include "EnemyMovmentState.h"

BaseEnemy::BaseEnemy(sf::Texture* tex, sfPos pos, b2World* world, Player* player)
	:BaseEntity(tex, pos, world), m_player(player), m_moveComponent(*this, nullptr)
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

    m_moveComponent.setState(std::move(enemyState));
}
void BaseEnemy::update(float deltaTime)
{
	BaseEntity::update(deltaTime);
	m_moveComponent.update(deltaTime);
}
