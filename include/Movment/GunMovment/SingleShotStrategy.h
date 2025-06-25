#pragma once
#include "ShootingStrategy.h"
#include "Factory.h"

class SingleShotStrategy : public ShootingStrategy {
public:
    std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos, sf::Vector2f direction, b2World* world) override {
        float gunLength = 36.f;
        sf::Vector2f dirNormalized = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f bulletPos = entityPos + dirNormalized * gunLength;

        auto bullet = Factory::instance().create(ObjectType::BULLET, bulletPos, world);
        bullet->setDirection(dirNormalized);

        std::vector<std::unique_ptr<BaseEntity>> bullets;
        bullets.push_back(std::move(bullet));
        return bullets;
    }
};
