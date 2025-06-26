#include "LifeGiftStrategy.h"
#include "Player.h"
#include "Gift.h"
#include "Factory.h"
#include "DataLoader.h"

static auto registerIt = Factory::instance().registerType(
    ObjectType::LifeGift,
    [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity> {
        return std::make_unique<Gift>(
            &DataLoader::getInstance().getP2Texture(ObjectType::characterSprite),
            pos,
            world,
            std::make_unique<LifeGiftStrategy>(),
            Direction::Right
        );
    });


void LifeGiftStrategy::applyEffect(Player& player) {
    player.addLife(1);
}