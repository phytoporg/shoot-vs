#include "Ship.h"

#include <cricket/resource/AssetLibrary.h>

#include <experimental/filesystem>

#include <vector>

#include <SFML/Graphics/Texture.hpp>

namespace 
{
    const int32_t Speed{300};
}

namespace ShootVs
{
    const std::string Ship::SheetAsset("ships.png");

    cricket::GameObjectPtr Ship::CreateObject(
        const cricket::AssetLibrary& assetLibrary,
        uint32_t shipType)
    {
        std::shared_ptr<GameObject> spObject;

        const std::vector<sf::IntRect> SpriteRegions = {
            sf::IntRect(0, 80, 84, 104) // Manually gathered in Gimp
        };

        if (shipType >= 0 && shipType < SpriteRegions.size())
        {
            namespace fs = std::experimental::filesystem;

            const fs::path RootPath(assetLibrary.GetRoot());
            const fs::path AssetPath(RootPath / SheetAsset);

            sf::Texture texture;
            if (texture.loadFromFile(
                AssetPath.generic_u8string(),
                SpriteRegions[shipType]))
            {
                spObject.reset(new Ship(texture));
            }
        }

        return spObject;
    }

    Ship::Ship(const sf::Texture& texture)
        : m_texture(texture)
    {
        m_sprite.setTexture(m_texture);
    }

    void Ship::Update(const sf::Time& dt)
    {
        const sf::Vector2f FloatVelocity(m_velocity);
        const float Length = 
            std::sqrt(FloatVelocity.x * FloatVelocity.x +
                      FloatVelocity.y * FloatVelocity.y);

        if (Length > 1e-6)
        {
            const sf::Vector2f Translation =
                dt.asSeconds() * Speed * (FloatVelocity / Length);
            m_sprite.move(Translation);
        }
    }

    void Ship::Draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    void Ship::SetPosition(const sf::Vector2i& position) 
    {
        sf::Vector2f FloatPosition(position);
        m_sprite.setPosition(FloatPosition);
    }
    
    sf::Vector2i Ship::GetPosition() const 
    {
        return sf::Vector2i(m_sprite.getPosition());
    }

    void Ship::SetVelocity(const sf::Vector2i velocity) 
    {
        m_velocity = velocity;
    }

    sf::Vector2i Ship::GetVelocity() const 
    {
        return sf::Vector2i(m_velocity);
    }
}

