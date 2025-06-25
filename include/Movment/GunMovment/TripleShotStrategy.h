#pragma once
#include "ShootingStrategy.h"
#include "Factory.h"

class TripleShotStrategy : public ShootingStrategy {
public:
    std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos, sf::Vector2f direction, b2World* world) override {
        std::vector<std::unique_ptr<BaseEntity>> bullets;

        float gunLength = 36.f;
        sf::Vector2f dirNormalized = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f bulletPos = entityPos + dirNormalized * gunLength;

        std::vector<sf::Vector2f> spread = {
            dirNormalized,
            rotate(dirNormalized, 10.f),
            rotate(dirNormalized, -10.f)
        };

        for (auto& dir : spread) {
            auto bullet = Factory::instance().create(ObjectType::BULLET, bulletPos, world);
            bullet->setDirection(dir);
            bullets.push_back(std::move(bullet));
        }

        return bullets;
    }

private:
    sf::Vector2f rotate(const sf::Vector2f& v, float degrees) {
        float radians = degrees * 3.14159f / 180.f;
        return {
            v.x * cos(radians) - v.y * sin(radians),
            v.x * sin(radians) + v.y * cos(radians)
        };
    }
};
