#pragma once

const float SCALE = 32.f; // Scale factor for Box2D to SFML conversion

enum class ObjectType
{
    PLAYER,
    SMURF,


    Enemy1,
    Enemy2,
    Tile,
    Explode,
    Gift,

    TemplateEnemy,
    BaseEnemy,
    AttackingEntity,
    MovingEntity,
    StaticEntity,
    BaseScreen,
    GamePlay
};