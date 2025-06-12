#include "Floor.h"	
#include "Factory/Factory.h"

static auto registesrIt = Factory::instance().registerType(
    ObjectType::FLOOR,
    [](sfPos, b2World*) -> std::unique_ptr<BaseEntity>
    {
        return std::make_unique<Floor>();
    }
);
Floor::Floor(sfPos pos, b2World* world)
	:StaticEntity(pos, world)
{
	auto invisibleTexture = createInvisibleTexture();
	initSprite(invisibleTexture);
	initBox2d(pos);
}

sf::Texture& Floor::createInvisibleTexture()
{
    static sf::Texture invisibleTexture;
    static bool textureCreated = false;

    if (!textureCreated) {
        sf::Image invisibleImage;
        invisibleImage.create(1, 1, sf::Color::Transparent); 
        invisibleTexture.loadFromImage(invisibleImage);
        textureCreated = true;
    }

    m_sprite.setTexture(invisibleTexture);
    m_sprite.setPosition(getPosition());

    m_sprite.setScale(SCREEN_WIDTH, 0.1f);
	return invisibleTexture;
}

