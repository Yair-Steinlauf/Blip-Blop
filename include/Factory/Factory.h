#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Constance.h"
//#include "BaseEntity.h"

class BaseEntity; // Forward declaration


class Factory
{
public:
    static Factory& instance()
    {
        static auto instance = Factory();
        return instance;
    }
    using FuncType = std::unique_ptr<BaseEntity>(*)(sfPos, b2World*);

    bool registerType(ObjectType t, FuncType f)
    {
        m_map.emplace(t, f);
        return true;
    }
    std::unique_ptr<BaseEntity> create(ObjectType t, sfPos pos, b2World* world)const
    {
		auto object = m_map.find(t);
		if (object == m_map.end()) 
            throw std::runtime_error("Cannot Find Current Object\n");
        return (object->second)(pos, world);
    }

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};