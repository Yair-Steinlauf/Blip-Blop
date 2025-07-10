#pragma once
#include "BaseEnemy.h"


class Player;


class ForkSmurf : public BaseEnemy {
public:
    ForkSmurf(sfPos pos = {50,50}, b2World* world = nullptr, Player* player = nullptr);
private:
    
};