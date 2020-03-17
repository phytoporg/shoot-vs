//
// Generic, abstract game object class.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace cricket
{
    class GameObject
    {
        public:
            GameObject() = default;
            virtual ~GameObject() = default;

            virtual void Update(const sf::Time& dt) = 0;
            virtual void Draw(sf::RenderWindow& window) = 0;

            //
            // Position
            //
            virtual void SetPosition(const sf::Vector2i& position) = 0;
            virtual sf::Vector2i GetPosition() const = 0;

            //
            // Velocity
            //
            virtual void SetVelocity(const sf::Vector2i velocity) = 0;
            virtual sf::Vector2i GetVelocity() const = 0;
    };

    using GameObjectPtr = std::shared_ptr<GameObject>;
}

