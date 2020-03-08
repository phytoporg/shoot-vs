//
// The whole wild world! Collection of game objects, effectively.
//

#pragma once

#include <vector>

#include "GameObject.h"

namespace cricket
{
    class World
    {
    public:
        World() = default;
        virtual ~World() = default;

        void Update();

        void AddObject(const GameObjectPtr& spObj);

        //
        // Returns false if the object can't be found (search by ptr address).
        //
        bool RemoveObject(const GameObjectPtr& spObj);

    private:
        std::vector<GameObjectPtr> m_objects;
    };
}

