//
// Generic, abstract game object class.
//

#pragma once

#include <memory>

namespace cricket
{
    class GameObject
    {
        public:
            GameObject() = default;
            virtual ~GameObject() = default;

            virtual void Update() = 0;
    };

    using GameObjectPtr = std::shared_ptr<GameObject>;
}

