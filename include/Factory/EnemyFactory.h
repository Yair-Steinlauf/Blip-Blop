#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Constance.h"
//#include "BaseEntity.h"


// Forward declaration
class BaseEntity;
class b2World;
class Player;

class EnemyFactory
{
public:
    static EnemyFactory& instance();
    using FuncType = std::unique_ptr<BaseEntity>(*)(sfPos, b2World*, Player*);

    bool registerType(ObjectType t, FuncType f);

    std::unique_ptr<BaseEntity> create(ObjectType t, sfPos pos, b2World* world, Player* player)const;
    std::unique_ptr<BaseEntity> createRandom(b2World* world, Player* player)const;

    std::vector<std::unique_ptr<BaseEntity>> createWave(int count, b2World* world, Player* player) const;
    

private:
    EnemyFactory() = default;
    EnemyFactory(const EnemyFactory&) = delete;
    void operator=(const EnemyFactory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};