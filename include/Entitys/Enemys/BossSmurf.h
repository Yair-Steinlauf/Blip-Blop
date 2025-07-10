#pragma once
#include "BaseEnemy.h"


class Player;


class BossSmurf : public BaseEnemy {
public:
    BossSmurf(sfPos pos = { 50,50 }, b2World* world = nullptr, Player* player = nullptr);
private:

};