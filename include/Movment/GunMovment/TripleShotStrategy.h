#pragma once
#include "ShootingStrategy.h"
#include "Factory.h"

class TripleShotStrategy : public ShootingStrategy {
public:
    std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos, sf::Vector2f direction, b2World* world) override {
        std::vector<std::unique_ptr<BaseEntity>> bullets;

        float gunLength = 36.f;
        float offsetAmount = 10.f;  // ���� ����� ������

        // ���������� �� ����� ����
        sf::Vector2f dirNormalized = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f bulletBasePos = entityPos + dirNormalized * gunLength;

        // ����� ���� ��dirNormalized (90 �����)
        sf::Vector2f perpendicular = { -dirNormalized.y, dirNormalized.x };

        // ����� ����� ��������
        std::vector<std::pair<sf::Vector2f, float>> spread = {
            { dirNormalized, 0.f },                     // �����
            { rotate(dirNormalized, 10.f), offsetAmount },   // ����
            { rotate(dirNormalized, -10.f), -offsetAmount }  // �����
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
