#pragma once
#include "BaseEnemy.h"


class Player;


class RegularSmurf : public BaseEnemy {
public:
    RegularSmurf(sfPos pos = { 50,50 }, b2World* world = nullptr, Player* player = nullptr);
private:

};