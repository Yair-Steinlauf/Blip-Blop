#pragma once
#include "BaseEntity.h"

class StaticEntity : public BaseEntity
{
public:

	StaticEntity(sfPos pos = { 50,50 }, b2World* world = nullptr);
	~StaticEntity() override = default;
};