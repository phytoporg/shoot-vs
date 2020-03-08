//
// The whole wild world! Collection of game objects, effectively.
//

#pragma once

#include "GameObject.h"

#include <vector>

#include <SFML/Graphics.hpp>

namespace cricket
{
    class World
    {
    public:
        World() = default;
        virtual ~World() = default;

        void Update(const sf::Time& dt);
        void Draw(sf::RenderWindow& window);

        void AddObject(const GameObjectPtr& spObj);

        //
        // Returns false if the object can't be found (search by ptr address).
        //
        bool RemoveObject(const GameObjectPtr& spObj);

    private:
        std::vector<GameObjectPtr> m_objects;
    };
}

