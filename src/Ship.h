//
// Spaceship object
//

#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Sprite.hpp>

#include <string>

namespace cricket
{
    class Ship : public GameObject
    {
        public:
            //
            // Ship type is basically just the "skin" of the ship.
            //
            // Supported values: 0-2
            //
            static GameObjectPtr CreateObject(uint32_t shipType);

            virtual void Update();

        private:
            Ship(uint32_t shipType);

            static const std::string SheetAsset;
            sf::Sprite m_sprite;
    };
}
