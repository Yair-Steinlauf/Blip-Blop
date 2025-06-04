#include "Player.h"

static auto registerIt = Factory::instance().registerType(
    ObjectType::Player,
    [](sf::Vector2f position) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<Player>(position);
    }
);