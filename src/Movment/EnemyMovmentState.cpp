#include "EnemyMovmentState.h"





std::unique_ptr<MovingState> EnemyMovementState::move()
{
    sfPos playerPos = m_getPlayerLoc();
    sfPos enemyPos = m_moveComponent.getEntity().getPosition();
    if (playerPos.x > enemyPos.x)
        m_moveComponent.setDirection({ 1,0 });
    else
        m_moveComponent.setDirection({ -1,0 });



    return nullptr;
}
