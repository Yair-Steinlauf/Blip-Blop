#pragma once
#include "BaseEntity.h"

class StaticEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	StaticEntity() = default;
	~StaticEntity() override = default;
};
