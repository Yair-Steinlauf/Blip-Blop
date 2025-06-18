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

DataLoader::DataLoader()
{

    //if (!m_font.loadFromFile("font.ttf"))
    //    // TODO: THrow exception here?
    //{
    //    std::cerr << "Failed to load font!" << std::endl;
    //}

    const std::vector<std::string> pictureList = {
        "pic1", "pic2"
    };

    const std::map<ObjectType, std::string> objectNames = {
        {ObjectType::PLAYER, "PLAYER"},
        {ObjectType::SMURF, "SMURF"},
        {ObjectType::MAP, "MAP"},
        //{ObjectType::Enemy2, "Enemy2"},
        //{ObjectType::Tile, "Tile"},
        //{ObjectType::Explode, "Explode"},
        //{ObjectType::Gift, "Gift"},
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
    //for (const auto& picName : pictureList)
    //{
    //    sf::Texture texture;
    //    if (texture.loadFromFile(picName + ".png"))
    //    {
    //        m_pictures.push_back(std::move(texture));
    //    }
    //    else
    //    {
    // 
	 // TODO: THrow exception here?
    //        std::cerr << "Failed to load texture: " << picName << ".png" << std::endl;
    //    }
    //}


}
