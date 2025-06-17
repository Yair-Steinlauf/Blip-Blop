#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Constance.h"
//#include "BaseEntity.h"

// Forward declaration
class BaseEntity; 
class b2World;

class Factory
{
public:
    static Factory& instance(); 
    using FuncType = std::unique_ptr<BaseEntity>(*)(sfPos, b2World*);

    bool registerType(ObjectType t, FuncType f);

    std::unique_ptr<BaseEntity> create(ObjectType t, sfPos pos, b2World* world)const;

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};