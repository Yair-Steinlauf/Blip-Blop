#pragma once
#include <SFML/Graphics.hpp>

const float SCALE = 30.f;

enum class ObjectType
{
    PLAYER,
    ForkSMURF,
    PresentSmurf,
    RegularSmurf,
    BossSmurf,
    PLATFORM,
    MAP,
    BULLET,
    characterSprite,
    spriteSheetSpecial,
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
    MenuScreen,
    HelpScreen,
    MenuBackground,
    PauseScreen,
    ResumeCommand,
    VictoryTexture,
    DefeatTexture,
    GameOverScreen,

    shotGunSound,
    shotGunWord,
    machineGunWord,
    BackgroundMusic,
    DeafultWeaponSound
};

enum class PlayerMovment {
	STAND,
	RIGHT,
	LEFT,
	JUMP
};

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const float PLAYER_FIXTURE_WIDTH = 40.f;
const float PLAYER_FIXTURE_HEIGHT = 28.f;
const float GUNLENGTH = 39.f;
const float BULLET_SPEED = 80.f;
const float BULLET_LIFETIME = 0.25f;
const float SIMPLE_SHOOT_TIME = 0.5f;
const float SINGLE_SHOOT_TIME = 0.1f;
const float TRIPLE_SHOOT_TIME = 1.f;

using sfPos = sf::Vector2f;

static float Box2dToSFML(float x) {
	return x * SCALE;
}
static float SFMLToBox2d(float x) {
	return x / SCALE;
}

