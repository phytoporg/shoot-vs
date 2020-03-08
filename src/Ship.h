//
// Spaceship object
//

#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <glm/glm.hpp>

#include <string>

namespace cricket
{
    //
    // Fordward decl
    //
    class AssetLibrary;

    class Ship : public GameObject
    {
        public:
            //
            // Ship type is basically just the "skin" of the ship.
            //
            // Supported values: 0-2... eventually. Right now, just 0.
            //
            static GameObjectPtr CreateObject(
                const AssetLibrary& assetLibrary,
                uint32_t shipType);

            virtual void Update(const sf::Time& dt) override;
            virtual void Draw(sf::RenderWindow& window) override;

            //
            // Position
            //
            virtual void SetPosition(const sf::Vector2i& position) override;
            virtual sf::Vector2i GetPosition() const override;

            //
            // Velocity
            //
            virtual void SetVelocity(const sf::Vector2i velocity) override;
            virtual sf::Vector2i GetVelocity() const override;

        private:
            Ship(const sf::Texture& texture);

            static const std::string SheetAsset;
            sf::Sprite   m_sprite;
            sf::Texture  m_texture;

            sf::Vector2i m_velocity;
    };
}

