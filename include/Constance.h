#pragma once
#include <SFML/Graphics.hpp>

const float SCALE = 30.f; // Scale factor for Box2D to SFML conversion

enum class ObjectType
{
    PLAYER,
    SMURF,
    PLATFORM,
    MAP,
    BULLET,
    characterSprite,
    Enemy1,
    Enemy2,
    Tile,
    Explode,
    LifeGift,
    TripleGift,
    SingleGift,
    TemplateEnemy,
    BaseEnemy,
    AttackingEntity,
    MovingEntity,
    StaticEntity,
    BaseScreen,
    GamePlay,

    shotGunSound,
    shotGunWord
};

enum class PlayerMovment {
	STAND,
	RIGHT,
	LEFT,
	JUMP
};

const int SCREEN_WIDTH = 800; // Window width
const int SCREEN_HEIGHT = 600; // Window height

const float PLAYER_FIXTURE_WIDTH = 40.f;
const float PLAYER_FIXTURE_HEIGHT = 28.f;
const float GUNLENGTH = 39.f;
const float BULLET_SPEED = 80.f;
const float BULLET_LIFETIME = 8.f;
const float SINGLE_SHOOT_TIME = 0.3f;
const float TRIPLE_SHOOT_TIME = 1.f;

using sfPos = sf::Vector2f;

static float Box2dToSFML(float x) {
	return x * SCALE;
}
static float SFMLToBox2d(float x) {
	return x / SCALE;
}

