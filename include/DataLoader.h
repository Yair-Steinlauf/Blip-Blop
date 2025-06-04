#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include "Factory.h"
#include <iostream>
#include <string>

class DataLoader
{
public:
    static DataLoader& getInstance();
    DataLoader(const DataLoader&) = delete;
    void operator=(const DataLoader&) = delete;
    static sf::Texture& getP2Texture(const enum ObjectType type);
    static sf::Texture& getP2Texture(int num);
    static sf::Font& getP2Font();

private:
    DataLoader();
    std::unordered_map<ObjectType, sf::Texture> m_textures;
    std::vector<sf::Texture> m_pictures;
    sf::Font m_font;
};
