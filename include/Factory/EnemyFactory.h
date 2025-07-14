#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "Constance.h"


class BaseEntity;
class b2World;
class Player;

class EnemyFactory
{
public:
    static EnemyFactory& instance();
    using FuncType =
        std::unique_ptr<BaseEntity>(*)(sfPos, b2World*, Player*);

    /* øéùåí èéôåñ */
    bool registerType(ObjectType t, FuncType f);

    /* éöéøä éùéøä */
    std::unique_ptr<BaseEntity> create(ObjectType  t,
        sfPos       pos,
        b2World* world,
        Player* player) const;

    /* øðãåîìé (ãâí éùï  ùðé àøâåîðèéí) */
    std::unique_ptr<BaseEntity> createRandom(b2World* world,
        Player* player) const;

    /* øðãåîìé áîé÷åí ñôöéôé (ãâí çãù) */
    std::unique_ptr<BaseEntity> createRandom(b2World* world,
        Player* player,
        sfPos    pos)  const;

    /* âì áúåê úçåí */
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
