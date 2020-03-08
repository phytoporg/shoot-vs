#include "World.h"
#include <algorithm>

namespace cricket
{
    void World::Update()
    {
        for (auto& spObject : m_objects)
        {
            spObject->Update();
        }
    }

    void World::AddObject(const GameObjectPtr& spObj)
    {
        m_objects.push_back(spObj);
    }

    bool World::RemoveObject(const GameObjectPtr& spObj)
    {
        using namespace std;
        auto it = find(begin(m_objects), end(m_objects), spObj);
        if (it == end(m_objects))
        {
            return false;
        }

        m_objects.erase(it);
        return true;
    }
}

