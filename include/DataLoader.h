#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    sf::Sound& getSound(ObjectType type);
    sf::Music& getMusic(ObjectType type);
private:
    DataLoader();
    std::unordered_map<ObjectType, sf::Texture> m_textures;
    std::vector<sf::Texture> m_pictures;
    sf::Font m_font;
    std::map<ObjectType, sf::SoundBuffer> m_soundBuffers;
    std::map<ObjectType, sf::Sound> m_sounds;
    std::map<ObjectType, sf::Music> m_music;
};
