#pragma once
#include "ShootingStrategy.h"
#include "Factory.h"

class TripleShotStrategy : public ShootingStrategy {
public:
    std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos, sf::Vector2f direction, b2World* world) override {
        std::vector<std::unique_ptr<BaseEntity>> bullets;

        float gunLength = 36.f;
        float offsetAmount = 10.f;  // מרחק ההטיה הצדדית

        // נורמליזציה של כיוון הירי
        sf::Vector2f dirNormalized = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f bulletBasePos = entityPos + dirNormalized * gunLength;

        // וקטור ניצב ל־dirNormalized (90 מעלות)
        sf::Vector2f perpendicular = { -dirNormalized.y, dirNormalized.x };

        // יצירת שלושת הכיוונים
        std::vector<std::pair<sf::Vector2f, float>> spread = {
            { dirNormalized, 0.f },                     // אמצעי
            { rotate(dirNormalized, 10.f), offsetAmount },   // ימני
            { rotate(dirNormalized, -10.f), -offsetAmount }  // שמאלי
        };

        for (const auto& [dir, offset] : spread) {
            sf::Vector2f finalPos = bulletBasePos + perpendicular * offset;

            auto bullet = Factory::instance().create(ObjectType::BULLET, finalPos, world);
            bullet->setDirection(dir);
            bullet->rotateToDirection(dir);
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
