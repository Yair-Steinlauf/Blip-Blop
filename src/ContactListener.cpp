#include "ContactListener.h"
#include "BaseEntity.h"

void ContactListener::BeginContact(b2Contact* contact) {
    uintptr_t userDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    uintptr_t userDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (userDataA && userDataB) {
        auto entityA = reinterpret_cast<BaseEntity*>(userDataA);
        auto entityB = reinterpret_cast<BaseEntity*>(userDataB);

        entityA->onCollisionEnter(entityB);
        entityB->onCollisionEnter(entityA);
    }
}

void ContactListener::EndContact(b2Contact* contact) {
    uintptr_t userDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    uintptr_t userDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (userDataA && userDataB) {
        auto entityA = reinterpret_cast<BaseEntity*>(userDataA);
        auto entityB = reinterpret_cast<BaseEntity*>(userDataB);

        entityA->onCollisionExit(entityB);
        entityB->onCollisionExit(entityA);
    }
}
