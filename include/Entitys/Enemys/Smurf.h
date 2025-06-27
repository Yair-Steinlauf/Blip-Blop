#pragma once
#include "BaseEnemy.h"


class Player;


class Smurf : public BaseEnemy {
public:
    Smurf(sfPos pos = {50,50}, b2World* world = nullptr, Player* player = nullptr);
private:
    
};