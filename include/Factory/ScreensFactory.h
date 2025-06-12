#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Constance.h"
#include "BaseScreen.h"


class ScreenFactory
{
public:
    static ScreenFactory& instance()
    {
        static auto instance = ScreenFactory();
        return instance;
    }

    using FuncType = std::unique_ptr<BaseScreen>(*)(sf::RenderWindow*);
    bool registerType(ObjectType t, FuncType f)
    {
        m_map.emplace(t, f);
        return true;
    }

    std::unique_ptr<BaseScreen> create(ObjectType t, sf::RenderWindow* window)const
    {
        auto object = m_map.find(t);
        if (object == m_map.end())
            throw std::runtime_error("Cannot Find Current Object\n");
        return (object->second)(window);
    }

private:
    ScreenFactory() = default;
    ScreenFactory(const ScreenFactory&) = delete;
    void operator=(const ScreenFactory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};