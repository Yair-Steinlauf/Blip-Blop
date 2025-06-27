#include "DataLoader.h"

DataLoader &DataLoader::getInstance()
{
    static DataLoader instance;
    return instance;
}

sf::Texture &DataLoader::getP2Texture(const enum ObjectType type)
{
    auto &instance = getInstance();
    auto it = instance.m_textures.find(type);
    if (it != instance.m_textures.end())
        return it->second;
    throw std::runtime_error("Texture not found for type: " + std::to_string(static_cast<int>(type)));
}

sf::Texture& DataLoader::getP2Texture(int num)
{
    auto& instance = getInstance();
    if (num < instance.m_pictures.size()) {
        return instance.m_pictures[num];
    }    
    throw std::runtime_error("Texture not found for type Pictures");
}

sf::Font &DataLoader::getP2Font()
{
    auto &instance = getInstance();
    return instance.m_font;
}

sf::Sound& DataLoader::getSound(ObjectType type) {
    auto& instance = getInstance();
    auto it = instance.m_sounds.find(type);
    if (it != instance.m_sounds.end())
        return it->second;
    throw std::runtime_error("Sound not found for ObjectType: " + std::to_string(static_cast<int>(type)));
}

DataLoader::DataLoader()
{
    const std::vector<std::string> pictureList = {
        "pic1", "pic2"
    };

    const std::map<ObjectType, std::string> objectNames = {
        {ObjectType::PLAYER, "PLAYER"},
        {ObjectType::SMURF, "SMURF"},
        {ObjectType::MAP, "MAP"},
        {ObjectType::characterSprite, "characterSprite"},
    };

    for (const auto &[type, name] : objectNames)
    {
        sf::Texture texture;
        if (texture.loadFromFile(name + ".png"))
        {
            m_textures[type] = std::move(texture);
        }
        else
        {
            // TODO: THrow exception here?
            std::cerr << "Failed to load texture: " << name << ".png" << std::endl;
        }
    }

    //  חדש: טעינת צלילים לפי ObjectType
    const std::map<ObjectType, std::string> soundNames = {
        {ObjectType::shotGunSound, "shotGunSound"},
        //{ObjectType::shotGunWord, "shotGunWord"},
        //{ObjectType::TripleGift, "tripleGunSound"},
        //{ObjectType::LifeGift, "lifeGainSound"}
    };

    for (const auto& [type, name] : soundNames) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(name + ".ogg")) {
            m_soundBuffers[type] = buffer;

            sf::Sound sound;
            sound.setBuffer(m_soundBuffers[type]);
            m_sounds[type] = sound;
        }
        else {
            std::cerr << "Failed to load sound: " << name << ".ogg\n";
        }
    }
}
