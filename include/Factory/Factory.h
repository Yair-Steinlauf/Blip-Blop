#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <functional>
enum class ObjectType
{
    PLAYER,
    SMURF,


    Enemy1,
    Enemy2,
    Tile,
    Explode,
    Gift,

    TemplateEnemy,
    BaseEnemy,
    AttackingEntity,
    MovingEntity,
    StaticEntity,
    BaseScreen,
    GamePlay
};

template <typename T>
class Factory
{
public:
    static Factory& instance()
    {
        static auto instance = Factory();
        return instance;
    }

    template <typename... Args>
    using FuncType = std::function<std::unique_ptr<T>(Args...)>;

    // Fixed: Added missing parameter name 'f'
    template <typename... Args>
        bool registerType(ObjectType t, FuncType<Args...> f)
    {
        // Convert to a generic callable that can be stored
        m_map[t] = [f](auto&&... args) -> std::unique_ptr<T> {
            return f(std::forward<decltype(args)>(args)...);
            };
        return true;
    }
	//template <typename... Args>
 //   using FuncType = std::unique_ptr<T>(*)(Args...);
 //   template <typename... Args>
 //   bool registerType(ObjectType t, FuncType)
 //   {
 //       m_map.emplace(t, f);
 //       return true;
 //   }

    template <typename... Args>
    std::unique_ptr<T> create(ObjectType t, Args&&... args)const
    {
		auto object = m_map.find(t);
		if (object == m_map.end()) 
            throw std::runtime_error("Cannot Find Current Object\n");
		return object->second(std::forward<Args>(args)...);
    }

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};