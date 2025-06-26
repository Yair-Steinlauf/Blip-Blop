#include "SingleShotGiftStrategy.h"  // <--- חובה!
#include "Player.h"
#include "Movment/GunMovment/SingleShotStrategy.h"
#include "DataLoader.h"
#include "Factory.h"
#include "Gift.h"

static auto registerTripleGift = Factory::instance().registerType(
    ObjectType::SingleTripleGift,
    [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity> {
        return std::make_unique<Gift>(
            &DataLoader::getInstance().getP2Texture(ObjectType::characterSprite),
            pos,
            world,
            std::make_unique<SingleShotGiftStrategy>(),
            Direction::Right
        );
    });

void SingleShotGiftStrategy::applyEffect(Player& player) {
    player.setGun(std::make_unique<SingleShotStrategy>(), AnimationSet::Blip, SINGLE_SHOOT_TIME);
}
