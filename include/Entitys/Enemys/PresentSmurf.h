#pragma once
#include "BaseEnemy.h"


class Player;


class PresentSmurf : public BaseEnemy {
public:
    PresentSmurf(sfPos pos = { 50,50 }, b2World* world = nullptr, Player* player = nullptr);
private:

};