#include "Ship.h"
#include <vector>

namespace cricket
{
    GameObjectPtr Ship::CreateObject(uint32_t shipType)
    {
        std::shared_ptr<GameObject> spObject;
        if (shipType >= 0 && shipType <= 2)
        {
            //spObject = std::make_shared<Ship>(shipType);
            spObject.reset(new Ship(shipType));
        }

        return spObject;
    }

    Ship::Ship(uint32_t shipType)
    {
        // TODO
    }

    void Ship::Update()
    {
        // TODO
    }
}

