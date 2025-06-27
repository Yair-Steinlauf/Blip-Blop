#include "Movment/GunMovment/SingleShotStrategy.h"
#include "Factory.h"

std::vector<std::unique_ptr<BaseEntity>> SingleShotStrategy::shoot(
    sf::Vector2f entityPos, sf::Vector2f direction, b2World* world)
{
    std::vector<std::unique_ptr<BaseEntity>> bullets;

    sf::Vector2f dirNormalized = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f bulletPos = entityPos + dirNormalized * GUNLENGTH;

    auto bullet = Factory::instance().create(ObjectType::BULLET, bulletPos, world);
    bullet->setDirection(dirNormalized);
    bullet->rotateToDirection(dirNormalized);

    bullets.push_back(std::move(bullet));
    return bullets;
}
