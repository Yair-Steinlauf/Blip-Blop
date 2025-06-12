#include "Floor.h"	
#include "Factory/Factory.h"

static auto registesrIt = Factory::instance().registerType(
    ObjectType::FLOOR,
    [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
    {
        std::cout << "Creating Floor at position: " << pos.x << ", " << pos.y << std::endl;
        return std::make_unique<Floor>(pos, world);
    }
);


Floor::Floor(sfPos pos, b2World* world)
	:StaticEntity(pos, world)
{
	//auto invisibleTexture = createInvisibleTexture();
	//initSprite(invisibleTexture);
	//initSprite(DataLoader::getP2Texture(ObjectType::PLAYER));
	//m_sprite.setTexture(DataLoader::getP2Texture(ObjectType::PLAYER));
	//m_sprite.setPosition({50,50});


    createVisibleTexture();
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

void Floor::createVisibleTexture()
{
    static sf::Texture floorTexture;
    static bool textureCreated = false;

    if (!textureCreated) {
        sf::Image floorImage;
        floorImage.create(64, 32, sf::Color::Red);
        floorTexture.loadFromImage(floorImage);
        textureCreated = true;
        std::cout << "Floor texture created successfully!" << std::endl;
    }

    initSprite(floorTexture);

    m_sprite.setScale(100.0f,0.5f);

    std::cout << "Floor sprite initialized at: " << m_sprite.getPosition().x
        << ", " << m_sprite.getPosition().y << std::endl;
}

void Floor::initBox2d(sfPos pos)
{
    BaseEntity::initBox2d(pos);
    b2FixtureDef fix;
    fix.shape = &m_polygonShape;
    fix.friction = 0.8f;      
    fix.restitution = 0.1f;   
    fix.density = 0.0f;
    m_fixture = m_body->CreateFixture(&fix);
}
