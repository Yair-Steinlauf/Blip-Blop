#include "TripleShotGiftStrategy.h"
#include "Player.h"
#include "Movment/GunMovment/TripleShotStrategy.h"
#include "DataLoader.h"
#include "Factory.h"
#include "Gift.h"

static auto registerTripleGift = Factory::instance().registerType(
    ObjectType::TripleGift,
    [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity> {
        return std::make_unique<Gift>(
            &DataLoader::getInstance().getP2Texture(ObjectType::characterSprite),
            pos,
            world,
            std::make_unique<TripleShotGiftStrategy>(),
            Direction::Right
        );
    });

void TripleShotGiftStrategy::applyEffect(Player& player) {
    player.setGun(std::make_unique<TripleShotStrategy>(), AnimationSet::Blip);
}
