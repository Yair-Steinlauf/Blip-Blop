#pragma once
#include <memory>
#include <unordered_map>
static enum ObjectType
{
    Player,
    TemplateEnemy,
    BaseEnemy,
    AttackingEntity,
    MovingEntity,
    StaticEntity,
    BaseScreen,
    GamePlay
};

template <typename T, typename... Args>
class Factory
{
public:
    static Factory& instance()
    {
        static auto instance = Factory();
        return instance;
    }

    using FuncType = std::unique_ptr<T>(*)(Args...);
    bool registerType(ObjectType t, FuncType f)
    {
        m_map.emplace(t, f);
        return true;
    }

    std::unique_ptr<T> create(ObjectType t, Args&&... args)const
    {
		auto object = m_map.find(t);
		if (object == m_map.end()) return nullptr;
		return object->second(std::forward<Args>(args)...);
    }

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};