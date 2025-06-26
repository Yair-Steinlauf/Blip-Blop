#include "EnemyMovmentState.h"



//TODO: Implement the enemy movement logic here

std::unique_ptr<MovingState> EnemyMovementState::move()
{
    sfPos playerPos = m_getPlayerLoc();
    sfPos enemyPos = m_moveComponent.getEntity().getPosition();
    if (playerPos.x > enemyPos.x)
        m_moveComponent.setDirection({ 1,0 });
    else
        m_moveComponent.setDirection({ -1,0 });
    //sf::Vector2f direction = calculateDirectionToPlayer(enemyPos, playerPos);
    //m_moveComponent.setDirection(direction);

    return nullptr;
}
