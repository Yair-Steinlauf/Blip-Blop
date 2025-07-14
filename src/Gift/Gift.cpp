
#include "Gift.h"
#include "Player.h"

Gift::Gift(sf::Texture* tex,
    sfPos pos,
    b2World* world,
    std::unique_ptr<IEffectStrategy> strategy,
    Direction direction)
    : BaseEntity(tex, pos, world),
    m_strategy(std::move(strategy))
{
    const sf::IntRect& frame =
        GameAnimations::getInstance().getFrame(AnimationSet::giftFrames, direction, 0);

    setTextureRect(frame);
    this->setFixtureForMov();
}

void Gift::onCollisionEnter(BaseEntity* other) {
    if (auto* player = dynamic_cast<Player*>(other)) {
        m_strategy->applyEffect(*player);
        this->markForRemoval();
    }
}
