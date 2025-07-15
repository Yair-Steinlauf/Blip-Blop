
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

    ignore_everyBody_exept_player();

}

void Gift::ignore_everyBody_exept_player()
{
    if (m_body) {
        m_body->SetType(b2_staticBody);
        m_body->SetLinearVelocity(b2Vec2(0, 0));
        m_body->SetAngularVelocity(0);

        for (b2Fixture* fixture = m_body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
            fixture->SetSensor(true);
        }
    }
}

void Gift::onCollisionEnter(BaseEntity* other) {
    if (auto* player = dynamic_cast<Player*>(other)) {
        m_strategy->applyEffect(*player);
        this->markForRemoval();
    }
}
