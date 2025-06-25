#include "EnemyMovmentState.h"



//TODO: Implement the enemy movement logic here

std::unique_ptr<MovingState> EnemyMovementState::move()
{
    sfPos playerPos = m_getPlayerLoc();
    sfPos enemyPos = m_moveComponent.getEntity().getPosition();

    sf::Vector2f direction = calculateDirectionToPlayer(enemyPos, playerPos);
    m_moveComponent.setDirection(direction);

    return nullptr;
}

sf::Vector2f EnemyMovementState::calculateDirectionToPlayer(const sfPos& enemyPos, const sfPos& playerPos) const
{
    // חישוב כיוון לשחקן
    float dx = playerPos.x - enemyPos.x;
    float dy = playerPos.y - enemyPos.y;

    // חישוב אורך הווקטור
    float magnitude = std::sqrt(dx * dx + dy * dy);

    // נרמול הווקטור
    if (magnitude > 0.0f) {
        dx /= magnitude;
        dy /= magnitude;
    }

    // רק תנועה אופקית (פלטפורמר)
    return { dx, 0.0f };
}