#pragma once
#include <memory>
#include <unordered_map>
#include <vector>            // ?vector
#include "Constance.h"

// forward declarations
class BaseEntity;
class b2World;
class Player;

class EnemyFactory
{
public:
    static EnemyFactory& instance();
    using FuncType =
        std::unique_ptr<BaseEntity>(*)(sfPos, b2World*, Player*);

    /*��� ����� ����� ���*/
    bool registerType(ObjectType t, FuncType f);

    /*��� ����� ����� ���*/
    std::unique_ptr<BaseEntity> create(ObjectType  t,
        sfPos       pos,
        b2World* world,
        Player* player) const;

    /*��� ������� (��� ��� � ��� ���������) ���*/
    std::unique_ptr<BaseEntity> createRandom(b2World* world,
        Player* player) const;

    /*��� ������� ������ ������ (��� ���) ���*/
    std::unique_ptr<BaseEntity> createRandom(b2World* world,
        Player* player,
        sfPos    pos)  const;

    /*��� �� ���� ���� ���*/
    std::vector<std::unique_ptr<BaseEntity>>
        createWave(int   count,
            b2World* world,
            Player* player,
            float    zoneLeft,
            float    zoneRight) const;

private:
    EnemyFactory() = default;
    EnemyFactory(const EnemyFactory&) = delete;
    EnemyFactory& operator=(const EnemyFactory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};
